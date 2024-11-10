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
    token = strtok(NULL, "^");  //token 3 times to get the starting address
    addr = strtol(token, NULL, 16);
    token = strtok(NULL, "^");  //token again to get the program length
    end = strtol(token, NULL, 16);
    prog_len = end-start;
    
    while(fgets(line, 256, finput)!=NULL){
        if(line[strlen(line)-1]=='\n'){
            line[strlen(line)-1] = 0; 
        }
        token = strtok(line, "^");  //token to get whether T or E record type
        if(line[0] == 'T'){
            token = strtok(NULL, "^");
            start = strtol(token, NULL, 16);
            if(start!=addr){
                addr = start;
            }

            token = strtok(NULL, "^");
            token = strtok(NULL, "^");  //token 2 times to access the object codesssss
            while(token!=NULL){
                length = strlen(token)/2;
                fprintf(foutput, "%X\t%s\n", addr, token);
                addr += length;
                token = strtok(NULL, "^");
            }
        }
        else if(line[0] == 'E'){
            printf("end");
        }
    }
}