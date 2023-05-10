#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum operaciones {
    nombre,
    calificacion,
    semestre, 
    generacion
};

void add_student(){
    FILE *file;
    file = fopen("practica2.bin", "rb+");
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

    fclose(file);
}

void prints_list(){
    char nombre[50];
    float calificacion;
    int semestre;
    int generacion;
    
    FILE *file;
    file = fopen("practica2.bin", "rb");
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
    fclose(file);
}

void buscar_alumno_y_eliminar(){
    char nombre[50];
    printf("Ingrese el nombre del alumno que desea eliminar: ");
    scanf("%s", nombre);

    FILE *archivo_lectura = fopen("practica2.bin", "rb");
    FILE *archivo_escritura = fopen("temp.bin", "wb");
    fseek(archivo_lectura, 0, SEEK_SET);
    fseek(archivo_escritura, 0, SEEK_SET);

    char nombre_actual[50];
    float calificacion;
    int generacion;
    int semestre;
    int encontrado = 0;
    fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
    fread(&calificacion, sizeof(float), 1, archivo_lectura);
    fread(&generacion, sizeof(int), 1, archivo_lectura);
    fread(&semestre, sizeof(int), 1, archivo_lectura);
    while (!feof(archivo_lectura)) {
        if (strcmp(nombre_actual, nombre) == 0) {
            encontrado = 1;
        } else {
            fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
            fwrite(&calificacion, sizeof(float), 1, archivo_escritura);
            fwrite(&semestre, sizeof(int), 1, archivo_escritura);
            fwrite(&generacion, sizeof(int), 1, archivo_escritura);
            
        }
        fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
        fread(&calificacion, sizeof(float), 1, archivo_lectura);
        fread(&semestre, sizeof(int), 1, archivo_lectura);
        fread(&generacion, sizeof(int), 1, archivo_lectura);
        
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

int numero_de_alumnos(char nombre[]){
    int counter=-1;
    FILE *file = fopen("practica2.bin", "rb");
    fseek(file, 0, SEEK_SET);
    char nombre_actual[50];
    float calificacion;
    int generacion, semestre;
    int encontrado = 0;

    while (fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, file) != 0) {
        fread(&calificacion, sizeof(float), 1, file);
        fread(&semestre, sizeof(int), 1, file);
        fread(&generacion, sizeof(int), 1, file);
        
        if (strcmp(nombre_actual, nombre) == 0) {
            counter++;
        }        
    }
    fclose(file);
    return counter;
}

void modificar(){
    char nombre[50];
    printf("Ingrese el nombre del alumno que desea modificar: ");
    scanf("%s", nombre);

    
    int num_alumnos=numero_de_alumnos(nombre);
    char nombre_actual[50];
    float calificacion;
    int generacion;
    int semestre;
    int encontrado = 0;
    float nueva_calificacion;
    int nueva_generacion;
    int nuevo_semestre;
    printf("%d", num_alumnos);
    FILE *archivo_lectura = fopen("practica2.bin", "rb");
    FILE *archivo_escritura = fopen("temp.bin", "wb");

    if(num_alumnos==1){
        float nueva_calificacion=0;
        printf("Dime la nueva calificacion: \n");
        scanf("%f", &nueva_calificacion);

        fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
        fread(&calificacion, sizeof(float), 1, archivo_lectura);
        fread(&semestre, sizeof(int), 1, archivo_lectura);
        fread(&generacion, sizeof(int), 1, archivo_lectura);
        
        while (!feof(archivo_lectura)) {
            if (strcmp(nombre_actual, nombre) == 0) {
                fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
                fwrite(&nueva_calificacion, sizeof(float), 1, archivo_escritura);
                fwrite(&semestre, sizeof(int), 1, archivo_escritura);
                fwrite(&generacion, sizeof(int), 1, archivo_escritura);
                
            } else {
                fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
                fwrite(&calificacion, sizeof(float), 1, archivo_escritura);
                fwrite(&semestre, sizeof(int), 1, archivo_escritura);
                fwrite(&generacion, sizeof(int), 1, archivo_escritura);
                
            }
            fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
            fread(&calificacion, sizeof(float), 1, archivo_lectura);
            fread(&semestre, sizeof(int), 1, archivo_lectura);
            fread(&generacion, sizeof(int), 1, archivo_lectura);
            
        }
        if (encontrado) {
            printf("El alumno ha sido eliminado correctamente.\n");
        } else {
            printf("No se encontro ningún alumno con ese nombre.\n");
        }
        
    } else if(num_alumnos>1){
        printf("Dame informacion extra.\n");
        float nueva_calificacion=0;
        printf("Dime la nueva calificacion: \n");
        scanf("%f", &nueva_calificacion);
        printf("Dime el semestre: ");
        scanf("%d", &nuevo_semestre);
        printf("Dime la generacion: ");
        scanf("%d", &nueva_generacion);
        fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
        fread(&calificacion, sizeof(float), 1, archivo_lectura);
        fread(&semestre, sizeof(int), 1, archivo_lectura);
        fread(&generacion, sizeof(int), 1, archivo_lectura);
        while (!feof(archivo_lectura)) {
            printf("%d %d %s\n", generacion, semestre, nombre_actual);
            if (strcmp(nombre_actual, nombre) == 0 && nueva_generacion == generacion 
                && nuevo_semestre == semestre  ) {
                fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
                fwrite(&nueva_calificacion, sizeof(float), 1, archivo_escritura);
                fwrite(&semestre, sizeof(int), 1, archivo_escritura);
                fwrite(&generacion, sizeof(int), 1, archivo_escritura);
                
            } else {
                fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
                fwrite(&calificacion, sizeof(float), 1, archivo_escritura);
                fwrite(&semestre, sizeof(int), 1, archivo_escritura);
                fwrite(&generacion, sizeof(int), 1, archivo_escritura);
            }
            fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
            fread(&calificacion, sizeof(float), 1, archivo_lectura);
            fread(&semestre, sizeof(int), 1, archivo_lectura);
            fread(&generacion, sizeof(int), 1, archivo_lectura);
            
        }
        
    } else {
        fclose(archivo_lectura);
        fclose(archivo_escritura);
        remove("temp.bin");
        return;
    } 
    //int opciones = menu_opciones();
    

    fclose(archivo_lectura);
    fclose(archivo_escritura);
    remove("practica2.bin");
    rename("temp.bin", "practica2.bin");
    
}

void buscar_alumno_y_mostrar(){
    char nombre[50];
    printf("Ingrese el nombre del alumno que desea buscar: ");
    scanf("%s", nombre);

    FILE *file = fopen("practica2.bin", "rb");

    char nombre_actual[50];
    float calificacion;
    int generacion, semestre;
    int encontrado = 0;

    while (fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, file) != 0) {
        fread(&calificacion, sizeof(float), 1, file);
        fread(&generacion, sizeof(int), 1, file);
        fread(&semestre, sizeof(int), 1, file);

        if (strcmp(nombre_actual, nombre) == 0) {
            printf("-------------------------------\n");
            printf("El nombres es: %s\n", nombre_actual);
            printf("La calificacion es: %f\n", calificacion);
            printf("El semestre es: %d\n", semestre);
            printf("La generacion es: %d\n", generacion);
            printf("-------------------------------\n");
        }        
    }
    fclose(file);
}

int menu_opciones(){
    int opcion=0;
    printf("Qué dato quiere modificar\n");
    printf("1. Nombre\n");
    printf("2. Semestre\n");
    printf("3. Carrera\n");
    printf("4. Calificacion\n");
    printf("5. Generaciones\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

void menu(){
    int opcion;

    while (1) {
        printf("MENU\n");
        printf("1. Agregar elemento\n");
        printf("2. Mostrar elementos\n");
        printf("3. Eliminar elemento por categoria: \n");
        printf("4. Mostrar elemento por categoria: \n");
        printf("5. Actualizar elemento por categoria: \n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("Ingrese los datos de estudiante: ");
                add_student();
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
                modificar();
            break;
            case 6:
                exit(EXIT_SUCCESS); // Sale del programa
            default:
                printf("Opcion invalida\n");
        }
    }
}

int main(){
    menu();
}