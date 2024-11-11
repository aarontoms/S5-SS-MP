#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main(){
    char label[10], opcode[20], operand[20], arguments[20], *token;
    char lab[10], opc[20], oper[20];
    char namtab[3][20], argtab[10][20];
    int ptr=0, argPtr=0, opFound=0;
    FILE *finput, *foutput, *fdeftab, *fnamtab, *fargtab;

    finput = fopen("input.txt", "r");
    foutput = fopen("output.txt", "w");
    fnamtab = fopen("namtab.txt", "w");
    fdeftab = fopen("deftab.txt", "w");
    fclose(fdeftab);

    while(fscanf(finput, "%s\t%s\t%s", label, opcode, operand)==3){
        if(strcmp(opcode, "MACRO")==0){
            argPtr=0;
            fprintf(fnamtab, "%s\n", label);
            strcpy(namtab[ptr], label);
            ptr++;
            strcpy(arguments, operand);
            token = strtok(arguments, ",");
            strcpy(argtab[argPtr], token);
            argPtr++;
            token = strtok(NULL, ",");
            while(token!=NULL){
                strcpy(argtab[argPtr], token);
                argPtr++;
                token = strtok(NULL, ",");
            }
            
            fdeftab = fopen("deftab.txt", "a");
            fprintf(fdeftab, "%s\t%s\t%s\n", label, opcode, operand);
            while(strcmp(opcode, "MEND")!=0){
                fscanf(finput, "%s\t%s\t%s", label, opcode, operand);
                int i;
                for(i=0; i<argPtr; i++){
                    if(strcmp(argtab[i], operand)==0){
                        fprintf(fdeftab, "%s\t%s\t?%d\n", label, opcode, i+1);
                        break;
                    }
                }
                if(i==argPtr){
                    fprintf(fdeftab, "%s\t%s\t%s\n", label, opcode, operand);
                }
            }
            fscanf(finput, "%s\t%s\t%s", label, opcode, operand);
            fclose(fdeftab);
        }
        
        int i;
        for(i=0; i<ptr; i++){
            if(strcmp(opcode, namtab[i])==0){
                argPtr=0;
                fargtab = fopen("argtab.txt", "w");
                token = strtok(operand,  ",");
                fprintf(fargtab, "%s\n", token);
                strcpy(argtab[argPtr], token);
                argPtr++;
                token = strtok(NULL,  ",");
                while(token!=NULL){
                    fprintf(fargtab, "%s\n", token);
                    strcpy(argtab[argPtr], token);
                    argPtr++;
                    token = strtok(NULL, ",");
                }
                fclose(fargtab);

                fdeftab = fopen("deftab.txt", "r");
                while(fscanf(fdeftab, "%s\t%s\t%s", lab, opc, oper)==3){
                    if(oper[0]=='?'){
                        oper[0] = oper[1];
                        oper[1] = 0;
                        printf("%s\n", argtab[atoi(oper)-1]);
                        fprintf(foutput, "%s\t%s\t%s\n", lab, opc, argtab[atoi(oper)-1]);
                    }
                }
                break;
            }

        }
        if(i==ptr){
            fprintf(foutput, "%s\t%s\t%s\n", label, opcode, operand);
        }
        
    }

    fclose(finput);
    fclose(foutput);
}