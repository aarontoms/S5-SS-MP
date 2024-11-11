#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
    int start, textstart, end, ptr=0, found=0, i, text_length=0, textptr=0;
    char addr[20], label[20], opcode[20], operand[20], name[20], text[100]="";
    char lab[20], opc[20], oper[20], mne[20], obj[20]="", objectcodes[20][20], textrecords[10][100];
    FILE *finter, *foptab, *frec, *fin;

    finter = fopen("intermediate.txt", "r");

    fscanf(finter, "%s\t%s\t%s", label, opcode, operand);
    strcpy(name, label);
    textstart = start = strtol(operand, NULL, 16);

    fscanf(finter, "%s\t%s\t%s\t%s", addr, label, opcode, operand);
    while(strcmp(opcode, "END")!=0){
        found=0;
        foptab = fopen("optab.txt", "r");
        while(fscanf(foptab, "%s\t%s", mne, opc)==2){
            if(strcmp(opcode, mne)==0){
                found = 1;
                strcat(obj, opc);
                fin = fopen("intermediate.txt", "r");
                fscanf(fin, "\t%s\t%s\t%s", lab, opc, oper);
                while(fscanf(fin, "%s\t%s\t%s\t%s", addr, lab, opc, oper)==4){
                    if(strcmp(operand, lab)==0){
                        strcat(obj, addr);
                        break;
                    }
                }
                fclose(fin);
                text_length += strlen(obj)/2;
                strcpy(objectcodes[ptr], obj);
                ptr++;
                strcpy(obj, "");
                break;
            }
        }
        fclose(foptab);

        if(found==0){
            if(strcmp(opcode, "WORD")==0){
                sprintf(obj, "%06s", operand);
                text_length += strlen(obj)/2;
                strcpy(objectcodes[ptr], obj);
                ptr++;
                strcpy(obj, "");
            }
            else if(strcmp(opcode, "BYTE")==0){
                char hex[5];
                int len = strlen(operand);
                for(int i=2; i<len-1; i++){
                    int ascii = (int)operand[i];
                    sprintf(hex, "%X", ascii);
                    strcat(obj, hex);
                }
                text_length += strlen(obj)/2;
                strcpy(objectcodes[ptr], obj);
                ptr++;
                strcpy(obj, "");
            }
        }
        if(text_length>15){
            sprintf(text, "T^%06X^%02X", textstart, (text_length-strlen(objectcodes[ptr-1])/2));
            for(int i=0; i<ptr-1; i++){
                strcat(text, "^");
                strcat(text, objectcodes[i]);
            }
            strcpy(textrecords[textptr], text);
            textptr++;

            strcpy(objectcodes[0], objectcodes[ptr-1]);
            ptr=1;
            textstart = strtol(addr, NULL, 16);
            text_length = strlen(objectcodes[0])/2;
            strcpy(text, "");
        }
        fscanf(finter, "%s\t%s\t%s\t%s", addr, label, opcode, operand);
    }
    sprintf(text, "T^%06X^%02X", textstart, text_length);
    for(int i=0; i<ptr; i++){
        strcat(text, "^");
        strcat(text, objectcodes[i]);
    }
    strcpy(textrecords[textptr], text);
    textptr++;

    end = strtol(addr, NULL, 16);

    frec = fopen("record.txt", "w");
    fprintf(frec, "H^%s^%06X^%06X\n\n", name, start, (end-start));
    for(int i=0; i<textptr; i++){
        fprintf(frec, "%s\n", textrecords[i]);
    }
    fprintf(frec, "\nE^%06X", start);
}