#include <stdio.h>
#include <stdlib.h>

struct estudiante {
    char nombre[50];
    float calificacion;
    int semestre;
    int generacion;
};

int main(){
    
    
    FILE *file = fopen("practica2.bin", "wb");
    char nombre[50];
    float calificacion;
    int semestre;
    int generacion;
    struct estudiante aux;
    for(int i=0; i<2; i++){
        scanf("%s", nombre);
        scanf("%f", &calificacion);
        scanf("%d", &semestre);
        scanf("%d", &generacion);
        fwrite(nombre, sizeof(51), 1, file);
        fwrite(&calificacion, sizeof(float), 1, file);
        fwrite(&semestre, sizeof(int), 1, file);
        fwrite(&generacion, sizeof(int), 1, file);
    }
    fclose(file);/*
    file = fopen("practica2.bin", "rb");
    
    fread(&aux, sizeof(struct estudiante), 1, file);
    while(!feof(file)){
        printf("%s ", aux.nombre);
        printf("%f ", aux.calificacion);
        printf("%d ", aux.semestre);
        printf("%d \n", aux.generacion);
        fread(&aux, sizeof(struct estudiante), 1, file);
    }*/
    fclose(file);
}