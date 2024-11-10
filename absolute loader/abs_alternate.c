#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int start, end, addr, length, prog_len;
    FILE *finput, *foutput;
    char line[256], *token;

    finput = fopen("input.txt", "r");
    foutput = fopen("output.txt", "w");

    fgets(line, 256, finput);
    token = strtok(line, "^");
    token = strtok(NULL, "^");
    token = strtok(NULL, "^");
    addr = strtol(token, NULL, 16);
    token = strtok(NULL, "^");
    end = strtol(token, NULL, 16);
    prog_len = end-start;
    
    while(fgets(line, 256, finput)!=NULL){
        if(line[strlen(line)-1]=='\n'){
            line[strlen(line)-1] = 0; 
        }
        token = strtok(line, "^");
        if(line[0] == 'T'){
            token = strtok(NULL, "^");
            start = strtol(token, NULL, 16);
            if(start!=addr){
                addr = start;
            }

            token = strtok(NULL, "^");
            token = strtok(NULL, "^");
            while(token!=NULL){
                length = strlen(token)/2;
                for(int i=0; i<length; i++){
                    fprintf(foutput, "%X\t%c%c\n", addr, token[i], token[i+1]);
                    addr++;
                }
                token = strtok(NULL, "^");
            }
        }
        else if(line[0] == 'E'){
            printf("end");
        }
    }
}