#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
    int start, end, offset=0, i, found, prev, flag;
    char label[20], opcode[20], operand[20];
    char lab[20], opc[20], oper[20], mne[20];
    FILE *finput, *foptab, *finter, *fsymtab, *fin;

    finput = fopen("input.txt", "r");
    finter = fopen("intermediate.txt", "w");
    fsymtab = fopen("symtab.txt", "w");

    fscanf(finput, "%s\t%s\t%s", label, opcode, operand);
    if(strcmp(opcode, "START")==0){
        start = strtol(operand, NULL, 16);
    }
    else{
        start = 0;
    }
    prev = start;
    fprintf(finter, "\t%s\t%s\t%s\n", label, opcode, operand);
    fscanf(finput, "%s\t%s\t%s", label, opcode, operand);
    while(strcmp(opcode, "END")!=0){
        found=0;
        foptab = fopen("optab.txt", "r");
        while(fscanf(foptab, "%s\t%s", mne, opc)==2){
            if(strcmp(opcode, mne)==0){
                found=1;
                offset += 3;
                break;
            }
        }
        fclose(foptab);
        if(found==0){
            if(strcmp(opcode, "WORD")==0){
                offset += 3;
            }
            else if(strcmp(opcode, "RESW")==0){
                offset += 3*atoi(operand);
            }
            else if(strcmp(opcode, "RESB")==0){
                offset += atoi(operand);
            }
            else if(strcmp(opcode, "BYTE")==0){
                offset += strlen(operand)-3;
            }
            else{
                printf("Invalid opcode.\n");
            }


            flag = -1;
            fin = fopen("input.txt", "r");
            while(fscanf(fin, "%s\t%s\t%s", lab, opc, oper)==3){
                if(strcmp(label, lab)==0){
                    flag++;
                }
            }
            fclose(fin);
            fprintf(fsymtab, "%X\t%s\t%d\n", prev, label, flag);
        }
        fprintf(finter, "%X\t%s\t%s\t%s\n", prev, label, opcode, operand);
        prev = start + offset;
        fscanf(finput, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(finter, "%X\t%s\t%s\t%s\n", prev, label, opcode, operand);
    fclose(finput);
    fclose(finter);
    
}