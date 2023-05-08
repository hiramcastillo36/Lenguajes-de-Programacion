#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum operaciones {
    nombre,
    calificacion,
    semestre, 
    generacion
};

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

void prints_list(){
    char nombre[50];
    float calificacion;
    int semestre;
    int generacion;
    //fseek(file, 0, SEEK_SET);
    FILE *file;
    file = fopen("practica2.bin", "rb+");
    
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

void buscar_alumno_y_eliminar(){
    char nombre[50];
    printf("Ingrese el nombre del alumno que desea eliminar: ");
    scanf("%s", nombre);

    FILE *archivo_lectura = fopen("practica2.bin", "rb");
    if (archivo_lectura == NULL) {
        printf("No se han guardado alumnos todavía.\n");
        return;
    }

    FILE *archivo_escritura = fopen("temp.bin", "wb");
    if (archivo_escritura == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char nombre_actual[50];
    float calificacion;
    int generacion, semestre;
    int encontrado = 0;

    while (fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura) != 0) {
        fread(&calificacion, sizeof(float), 1, archivo_lectura);
        fread(&generacion, sizeof(int), 1, archivo_lectura);
        fread(&semestre, sizeof(int), 1, archivo_lectura);

        if (strcmp(nombre_actual, nombre) == 0) {
            encontrado = 1;
        } else {
            fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
            fwrite(&calificacion, sizeof(float), 1, archivo_escritura);
            fwrite(&generacion, sizeof(int), 1, archivo_escritura);
            fwrite(&semestre, sizeof(int), 1, archivo_escritura);
        }
    }
    if (encontrado) {
        printf("El alumno ha sido eliminado correctamente.\n");
    } else {
        printf("No se encontro ningún alumno con ese nombre.\n");
    }

    fclose(archivo_lectura);
    fclose(archivo_escritura);

    remove("practica2.bin");
    rename("temp.bin", "practica2.bin");
    
}
void buscar_alumno_y_mostrar(){
    char nombre[50];
    printf("Ingrese el nombre del alumno que desea buscar: ");
    scanf("%s", nombre);

    FILE *archivo_lectura = fopen("practica2.bin", "rb");
    if (archivo_lectura == NULL) {
        printf("No se han guardado alumnos todavía.\n");
        return;
    }

    char nombre_actual[50];
    float calificacion;
    int generacion, semestre;
    int encontrado = 0;

    while (fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura) != 0) {
        fread(&calificacion, sizeof(float), 1, archivo_lectura);
        fread(&generacion, sizeof(int), 1, archivo_lectura);
        fread(&semestre, sizeof(int), 1, archivo_lectura);

        if (strcmp(nombre_actual, nombre) == 0) {
            encontrado = 1;
            printf("-------------------------------\n");
            printf("El nombres es: %s\n", nombre_actual);
            printf("La calificacion es: %f\n", calificacion);
            printf("El semestre es: %d\n", semestre);
            printf("La generacion es: %d\n", generacion);
            printf("-------------------------------\n");
        } 
            
    }
    if (encontrado) {
        printf("El alumno ha sido encontrado correctamente.\n");
    } else {
        printf("No se encontro ningún alumno con ese nombre.\n");
    }

    fclose(archivo_lectura);
    
}
void eliminar(FILE *file){
    int op=0;
    scanf("%d", &op);
    switch (op){
        case nombre:
            printf("nombre");
            break;
        case calificacion:
            printf("calificacion");
            break;
        case semestre:
        printf("semestre");
            break;
        case generacion:
            printf("generai");
            break;
        default:
            printf("eoeore");
        break;
    }
    
}

void menu(FILE *file){
    int opcion;

    while (1) {
        printf("MENU\n");
        printf("1. Agregar elemento\n");
        printf("2. Mostrar elementos\n");
        printf("3. Eliminar elemento por categoria: \n");
        printf("4. Mostrar elemento por categoria: \n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("Ingrese los datos de estudiante: ");
                add_student(file);
                break;
            case 2:
                printf("Lista de estudiantes: \n");
                prints_list();
                break;
            case 3:
                buscar_alumno_y_eliminar();
            break;
            case 4:
                buscar_alumno_y_mostrar();
            break;
            case 5:
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