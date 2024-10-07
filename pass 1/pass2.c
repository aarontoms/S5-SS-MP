#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<math.h>

void main(){
    char label[20], opcode[20], operand[20], addr[20], obj[20];
    char a[20], b[20], c[20], d[20];
    char *labels[50];
    long offset=0;

    FILE *finput, *fint, *foptab, *fsymtab, *ftester, *foutput, *ftester2, *frecord;
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
        printf("HEX: %d\n", hex);
        fprintf(fint, "\t%s\t%s\t%s\n", label, opcode, operand);
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
        
            fprintf(fsymtab, "%s\t%X\t%d\n", label, prev, flag);
            // printf("aaaaa: %d\n", atoi(label));
        }

        fprintf(fint, "%X\t%s\t%s\t%s\n", prev, label, opcode, operand);
        // printf("%X\t%s\t%s\t%s\n", prev, label, opcode, operand);
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
    fscanf(fint, "\t%s\t%s\t%s", label, opcode, operand);
    fprintf(foutput, "\t%s\t%s\t%s\n", label, opcode, operand);

    int lenOpcode=0, top=0;
    char objectCode[20][20];
    char address[20][20];
    while(!strcmp(opcode, "END")==0){
        found = 0;
        strcpy(obj, "");
        fscanf(fint, "%s\t%s\t%s\t%s", addr, label, opcode, operand);

        ftester = fopen("optab.txt", "r");
        while (fscanf(ftester, "%99s %99s", a, b)==2) {
            if(strcmp(a, opcode)==0){
                lenOpcode += 6;
                found = 1;
                strcpy(obj, b);
                ftester2 = fopen("intermediate.txt", "r");
                fscanf(ftester2, "%X\t%s\t%s\t%s", a, b, c, d);
                while (fscanf(ftester2, "%99s %99s %99s %99s", a, b, c, d)==4) {
                    if(strcmp(operand, b)==0){
                        strcat(obj, a);
                    }
                }
                fclose(ftester2);
                strcpy(objectCode[top], obj);
                strcpy(address[top], addr);
                // printf("\nAdded: %s ", objectCode[0]);
                top++;
                // printf("%s\t%s\t%s\t%s\t%s\n", addr, label, opcode, operand, obj);
                break;
            }
        }
        fclose(ftester);

        if(found == 0){
            if(strcmp(opcode, "WORD")==0){
                lenOpcode += 6;
                strcpy(obj, "");
                // int len = strlen(operand);
                // for (int i=0; i<6-len; i++) {
                //     strcat(obj, "0");
                // }
                // strcat(obj, operand);
                sprintf(obj, "%06s", operand);
                strcpy(objectCode[top], obj);
                strcpy(address[top], addr);
                top++;
            }
            else if(strcmp(opcode, "BYTE")==0){
                printf("TOP: %d\n", top);
                int len = strlen(operand);
                int ascii;
                char hex[3];
                for (int i=2; i<len-1; i++) {
                    ascii = (int)operand[i];
                    sprintf(hex, "%02X", ascii);
                    strcat(obj, hex);
                }
                lenOpcode += strlen(obj);
                strcpy(objectCode[top], obj);
                strcpy(address[top], addr);
                top++;
            }
        }
        // printf("TOP: %d\n", top);
        // printf("%s\t%s\t%s\t%s\t%s\n", addr, label, opcode, operand, obj);
        // printf("found and opcode: %d and %s\n", found, opcode);
        fprintf(foutput, "%s\t%s\t%s\t%s\t%s\n", addr, label, opcode, operand, obj);
    }
    fclose(fint);
    fclose(foptab);
    fclose(fsymtab);
    fclose(foutput);

    long start, end, start2;
    fint = fopen("intermediate.txt", "r");
    fscanf(fint, "%s\t%s\t%s", addr, a, opcode, operand);
    fscanf(fint, "%s\t%s\t%s\t%s", addr, label, opcode, operand);
    start2 = start = strtol(addr, NULL, 16);
    while(!strcmp(opcode, "END")==0){
        fscanf(fint, "%s\t%s\t%s\t%s", addr, label, opcode, operand);
    }
    end = strtol(addr, NULL, 16);
    fclose(fint);
    // printf("start, end: %06x\n", end-start);

    for(int i=0; i<top; i++){
        printf("%s\n", objectCode[i]);
    }
    frecord = fopen("record.txt", "w");
    fprintf(frecord, "H^%s^%X^%06X\n\n", a, start, end-start);
    lenOpcode /= 2;
    printf("lenOpcode: %d\n", lenOpcode);

    int count=0;
    char text[50] = "";
    int len=0;
    while(count<top){
        len += strlen(objectCode[count]);

        if(len>30){
            len -= strlen(objectCode[count]);
            fprintf(frecord, "T^%06X^%02X%s\n", start, len/2, text);
            strcpy(addr, address[count]);
            start = strtol(addr, NULL, 16);
            
            len = strlen(objectCode[count]);
            strcpy(text, "");
        }
        strcat(text, "^");
        strcat(text, objectCode[count]);
        count++;
    }
    fprintf(frecord, "T^%06X^%02X%s\n", start, len/2, text);

    fprintf(frecord, "\nE^%06X", start2);
}