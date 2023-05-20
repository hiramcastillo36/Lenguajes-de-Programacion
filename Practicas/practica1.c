#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    char cadena[100];
    FILE *file = fopen("practica.txt", "r");
    if(file==NULL){
        printf("El archivo no existe");
        return 0;
    } 
    while(!feof(file)){
        fscanf(file, "%s", cadena);
        if (strlen(cadena)!=0) 
            printf("%s ", cadena);
        else 
            printf("\n");
    }
    fclose(file);
}