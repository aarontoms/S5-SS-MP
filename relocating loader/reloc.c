#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
    char line[256], *token, relocAddr[10];
    int prog_start, addr, start, length, relocAddrInt, modificationArr[10][3], ptr=0;
    FILE *finput, *foutput, *faddress;
    finput = fopen("input.txt", "r");

    printf("Enter the new address: ");
    scanf("%s", relocAddr);
    relocAddrInt = strtol(relocAddr, NULL, 16);

    fgets(line, 256, finput);
    token = strtok(line, "^");
    token = strtok(NULL, "^");
    token = strtok(NULL, "^");
    prog_start =  addr = strtol(token, NULL, 16);

    faddress = fopen("address.txt", "w");
    while(fgets(line, 256, finput)!=NULL){
        if(line[strlen(line)-1] == '\n'){
            line[strlen(line)-1] = 0;
        }
        if(line[0] == 'T'){
            token = strtok(line, "^");
            token = strtok(NULL, "^");
            start = strtol(token, NULL, 16);
            if(start != addr){
                addr = start;
            }

            token = strtok(NULL, "^");
            token = strtok(NULL, "^");
            while(token != NULL){
                addr += strlen(token)/2;
                fprintf(faddress, "%d\t%s\n", (addr-prog_start), token);
                token = strtok(NULL, "^");
            }
        }
        else if(line[0] == 'M'){
            token = strtok(line, "^");
            token = strtok(NULL, "^");
            int modif = strtol(token, NULL, 16);
            modificationArr[ptr][0] = modif;
            ptr++;
        }
    }
    fclose(faddress);
    fclose(finput);

    for(int i=0; i<ptr; i++){
        int address, obj;
        char objectcode[20];
        int modif = modificationArr[i][0];
        faddress = fopen("address.txt", "r");
        while(fscanf(faddress, "%d\t%s", &address, objectcode)==2){
            if(modif<=address){
                obj = strtol(objectcode, NULL, 16);
                modificationArr[i][1] = obj;
                obj += (relocAddrInt-prog_start);
                modificationArr[i][2] = obj;
                break;
            }
        }
        fclose(faddress);
    }

    finput = fopen("input.txt", "r");
    foutput = fopen("output.txt", "w");
    int ptr2=0;
    while(fgets(line, 256, finput) != NULL){
        if(line[strlen(line)-1] == '\n'){
            line[strlen(line)-1] = 0;
        }

        if(line[0]=='H'){
            fprintf(foutput, "%s\n", line);
        }
        else if(line[0] == 'T'){
            token = strtok(line, "^");
            fprintf(foutput, "\n%s", token);
            token = strtok(NULL, "^");
            fprintf(foutput, "^%s", token);
            token = strtok(NULL, "^");
            fprintf(foutput, "^%s", token);
            token = strtok(NULL, "^");
            while(token != NULL){
                if(strtol(token, NULL, 16) == modificationArr[ptr2][1]){
                    fprintf(foutput, "^%X", modificationArr[ptr2][2]);
                    ptr2++;
                }
                else{
                    fprintf(foutput, "^%s", token);
                }
                token = strtok(NULL, "^");
            }
        }
        else if(line[0]=='E'){
            fprintf(foutput, "\n\n%s\n", line);
        }
    }
}