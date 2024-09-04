#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){
    char label[20];
    char opcode[20];
    char operand[20];
    char a[20], b[20], c[20];
    char *labels[50];
    long offset=0;

    FILE *f1, *fint, *foptab, *fsymtab, *ftester;
    f1 = fopen("input.txt", "r");
    foptab = fopen("optab.txt", "r");
    fint = fopen("intermediate.txt", "w");
    fsymtab = fopen("symtab.txt", "w");
    int intOperand, temp, hex=0, prev;

    fscanf(f1, "%s\t%s\t%s", label, opcode, operand);
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
        fscanf(f1, "%s\t%s\t%s", label, opcode, operand);
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

            fprintf(fsymtab, "%s\t%x\t%d\n", label, prev, flag);
            // printf("aaaaa: %d\n", atoi(label));
        }

        fprintf(fint, "%x\t%s\t%s\t%s\n", prev, label, opcode, operand);
        prev = (hex+offset);
    }while(!strcmp(opcode, "END")==0);
}
