#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_student(FILE *file){
    fseek(file, 0, SEEK_END);
    char nombre[50];
    float calificacion;
    int semestre;
    int generacion;
    printf("Dime el nombre: ");
    scanf("%s", nombre);
    printf("Dime la calificacion: ");
    scanf("%f", &calificacion);
    printf("Dime el semestre: ");
    scanf("%d", &semestre);
    printf("Dime la generacion: ");
    scanf("%d", &generacion);
    fwrite(nombre, sizeof(strlen(nombre)), 1, file);
    fwrite(&calificacion, sizeof(float), 1, file);
    fwrite(&semestre, sizeof(int), 1, file);
    fwrite(&generacion, sizeof(int), 1, file);
}

void prints_list(FILE *file){
    char nombre[50];
    float calificacion;
    int semestre;
    int generacion;
    fseek(file, 0, SEEK_SET);
    fread(nombre, sizeof(strlen(nombre)), 1, file);
    fread(&calificacion, sizeof(float), 1, file);
    fread(&semestre, sizeof(int), 1, file);
    fread(&generacion, sizeof(int), 1, file);
    while(!feof(file)){
        printf("El nombres es: %s\n", nombre);
        printf("La calificacion es: %f\n", calificacion);
        printf("El semestre es: %d\n", semestre);
        printf("La generacion es: %d\n", generacion);
        printf("-------------------------------\n");
        fread(nombre, sizeof(strlen(nombre)), 1, file);
        fread(&calificacion, sizeof(float), 1, file);
        fread(&semestre, sizeof(int), 1, file);
        fread(&generacion, sizeof(int), 1, file);
    }
}

void menu(FILE *file){
    int opcion;

    while (1) {
        printf("MENU\n");
        printf("1. Agregar elemento\n");
        printf("2. Mostrar elementos\n");
        printf("3. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("Ingrese los datos de estudiante: ");
                add_student(file);
                break;
            case 2:
                printf("Lista de estudiantes: \n");
                prints_list(file);
                break;
            case 3:
                exit(EXIT_SUCCESS); // Sale del programa
            default:
                printf("Opcion invalida\n");
        }
    }
}

int main(){
    FILE *file;
    file = fopen("practica2.bin", "rb+");
    menu(file);
    fclose(file);
}