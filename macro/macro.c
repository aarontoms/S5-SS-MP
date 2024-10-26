#include<stdio.h>
#include<stdlib.h>

void main(){
    char label[20], opcode[20], operand[20], addr[20], obj[20];
    char a[20], b[20], c[20], d[20];
    char namtab[5][20], deftab[5][20];
    int  ptr=0;

    FILE *finput, *fdeftab, *fnamtab, *ftester, *foutput;

    finput = fopen("input.txt", "r");
    foutput = fopen("output.txt", "w");
    while(strcmp(opcode, "END")!=0){
        fscanf(finput, "%s\t%s\t%s", label, opcode, operand);

        if(strcmp(opcode, "MACRO")==0){
            // namm();
            strcpy(namtab[ptr], label);
            ptr++;
            fnamtab = fopen("namtab.txt", "w");
            fprintf(fnamtab, "%s", label);
            fclose(namtab);

            // deff();
            fdeftab = fopen("deftab.txt", "w");
            fscanf(finput, "%s\t%s\t%s", label, opcode, operand);
            while(strcmp(opcode, "MEND")!=0){
                fprintf(fdeftab, "%s\t%s\t%s\n", label, opcode, operand);
                fscanf(finput, "%s\t%s\t%s", label, opcode, operand);
            }
            fclose(fdeftab);

            continue;
        }
        if(strcmp(opcode, "MAC")==0){
            printf("keri");
            ftester = fopen("input.txt", "r");
            while(strcmp(a, opcode)!=0){
                fscanf(ftester, "%s\t%s\t%s", a, b, c);
            }
            fscanf(ftester, "%s\t%s\t%s", a, b, c);
            while(strcmp(b, "MEND")!=0){
                fprintf(foutput, "%s\t%s\t%s\n", a, b, c);
                fscanf(ftester, "%s\t%s\t%s", a, b, c);
            }
            continue;
        }

        fprintf(foutput, "%s\t%s\t%s\n", label, opcode, operand);
    }

    for(int i=0; i<ptr; i++){
        printf("MACRO: %s, ", namtab[i]);
        printf("DEFINITION: %s\n", deftab[i]);
    }
}
