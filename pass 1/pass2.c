#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){
    char label[20];
    char opcode[20];
    char operand[20];
    char addr[20];
    char obj[20];
    char a[20], b[20], c[20], d[20];
    char *labels[50];
    long offset=0;

    FILE *finput, *fint, *foptab, *fsymtab, *ftester, *foutput, *ftester2;
    finput = fopen("input.txt", "r");
    foptab = fopen("optab.txt", "r");
    fint = fopen("intermediate.txt", "w");
    fsymtab = fopen("symtab.txt", "w");
    int intOperand, temp, hex=0, prev, found;

    fscanf(finput, "%s\t%s\t%s", label, opcode, operand);
    if(strcmp(opcode, "START")==0){
        // printf("Starting");
        temp = atoi(operand);
        int place=-1;
        while(temp>0){
            int digit = temp%10;
            place++;
            // printf("%d^%d    ", 16, place);
            hex += digit * pow(16, place);
            temp = temp/10;
        printf("HEX is: %d\n", hex);
        }
        printf("HEX: %d", hex);
        fprintf(fint, "\t\t%s\t%s\t%s\n", label, opcode, operand);
        prev = hex;
    }

    do{
        fscanf(finput, "%s\t%s\t%s", label, opcode, operand);
        // printf("%s %s %s", label, opcode, operand);

        if(strcmp(opcode, "WORD")==0){
            offset += 3;
        }
        else if(strcmp(opcode, "RESW")==0){
            intOperand = atoi(operand);
            offset += (3*intOperand);
        }
        else if(strcmp(opcode, "RESB")==0){
            offset += atoi(operand);
        }
        else if(strcmp(opcode, "BYTE")==0){
            int length = strlen(operand) - 3;
            offset += length;
        }
        else{
            offset += 3;
        }

        if(strcmp(label, "-")!=0){
            int flag = -1;

            ftester = fopen("input.txt", "r");
            fscanf(ftester, "%s\t%s\t%s", a, b, c);
            while(!strcmp(b, "END")==0){
                fscanf(ftester, "%s\t%s\t%s", a, b, c);
                if(strcmp(label, a)==0){
                    flag++;
                }
            }
            fclose(ftester);
        
            fprintf(fsymtab, "%s\t%x\t%d\n", label, prev, flag);
            // printf("aaaaa: %d\n", atoi(label));
        }

        fprintf(fint, "%x\t%s\t%s\t%s\n", prev, label, opcode, operand);
        prev = (hex+offset);
    }while(!strcmp(opcode, "END")==0);

    fclose(finput);
    fclose(fint);
    fclose(foptab);
    fclose(fsymtab);

    fint = fopen("intermediate.txt", "r");
    foptab = fopen("optab.txt", "r");
    fsymtab = fopen("symtab.txt", "r");
    foutput = fopen("output.txt", "w");
    fscanf(fint, "%x\t%s\t%s\t%s", addr, label, opcode, operand);

    while(!strcmp(opcode, "END")==0){
        found = 0;
        strcpy(obj, "");
        fscanf(fint, "%s\t%s\t%s\t%s", addr, label, opcode, operand);

        ftester = fopen("optab.txt", "r");
        while (fscanf(ftester, "%99s %99s", a, b)==2) {
            if(strcmp(a, opcode)==0){
                found = 1;
                strcpy(obj, b);
                ftester2 = fopen("intermediate.txt", "r");
                fscanf(ftester2, "%x\t%s\t%s\t%s", a, b, c, d);
                while (fscanf(ftester2, "%99s %99s %99s %99s", a, b, c, d)==4) {
                    if(strcmp(operand, b)==0){
                        strcat(obj, a);
                    }
                }
                printf("%s\t%s\t%s\t%s\t%s\n", addr, label, opcode, operand, obj);
                break;
            }
        }
        fclose(ftester);

        if(!found){
            if(strcmp(opcode, "WORD")==0){
                temp = atoi(operand);
                printf("--%d--\n", temp);
                strcpy(obj, temp);
            }
        }
        printf("%s\t%s\t%s\t%s\t%s\n", addr, label, opcode, operand, obj);
        fprintf(foutput, "%s\t%s\t%s\t%s\t%s\n", addr, label, opcode, operand, obj);
    }

}
