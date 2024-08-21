#include<stdio.h>

void main(){
    char data[50];
    int i=0;
    FILE *fptr;
    fptr = fopen("input.txt", "r");

    fgets(data, 50, fptr);
    printf("%s\n", data);
    while (data[i] != '\0') {
        if (data[i] == ' ') {
            printf("Space found at position: %d\n", i);
        }
        i++;
    }
    fclose(fptr);
}
