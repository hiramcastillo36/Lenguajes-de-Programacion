#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum operaciones {
    nombre,
    calificacion,
    semestre, 
    generacion, 
    carrera
};

void add_student(){
    FILE *file;
    file = fopen("practica2.bin", "rb+");
    if(file == NULL){
        file = fopen("practica2.bin", "wb+");
    } else 
        fseek(file, 0, SEEK_END);
    char nombre[50];
    float calificacion;
    int semestre;
    int generacion;
    char carrera[50];
    printf("Dime el nombre: ");
    scanf("%s", nombre);
    printf("Dime la calificacion: ");
    scanf("%f", &calificacion);
    printf("Dime el semestre: ");
    scanf("%d", &semestre);
    printf("Dime la generacion: ");
    scanf("%d", &generacion);
    printf("Dime la carrera: ");
    scanf("%s", carrera);
    fwrite(nombre, sizeof(strlen(nombre)), 1, file);
    fwrite(&calificacion, sizeof(float), 1, file);
    fwrite(&semestre, sizeof(int), 1, file);
    fwrite(&generacion, sizeof(int), 1, file);
    fwrite(carrera, sizeof(strlen(carrera)), 1, file);
    fclose(file);
}

void header(){
    for(int i=0; i<125; i++)
        printf("-");
    printf("\n|                 Nombre                 |    Calificacion   |       Carrera      |      Semestre      |     Generacion     |\n");
    for(int i=0; i<125; i++)
        printf("-");
    printf("\n");    
}

void print_student(
                    char nombre[50],
                    float calificacion,
                    int semestre,
                    int generacion,
                    char carrera[50]
                ){
    printf("|%-40s|%-19.2f|%-20s|%-20d|%-20d|\n", nombre, calificacion, carrera, semestre, generacion);
    for(int i=0; i<125; i++)
        if(i%2)printf("-");
        else printf(" ");
    printf("\n");
    
}

void prints_list(){
    char nombre[50];
    char carrera[50];
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
    fread(carrera, sizeof(strlen(carrera)), 1, file);
    header();
    while(!feof(file)){
        print_student(nombre, calificacion, semestre, generacion, carrera);
        fread(nombre, sizeof(strlen(nombre)), 1, file);
        fread(&calificacion, sizeof(float), 1, file);
        fread(&semestre, sizeof(int), 1, file);
        fread(&generacion, sizeof(int), 1, file);
        fread(carrera, sizeof(strlen(carrera)), 1, file);
    }
    fclose(file);
}
int numero_de_alumnos(char nombre[]){
    int counter=0;
    FILE *file = fopen("practica2.bin", "rb");
    fseek(file, 0, SEEK_SET);
    char nombre_actual[50], carrera[50];
    float calificacion;
    int generacion, semestre;
    int encontrado = 0;
    
    fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, file);
    fread(&calificacion, sizeof(float), 1, file);
    fread(&semestre, sizeof(int), 1, file);
    fread(&generacion, sizeof(int), 1, file);
    fread(carrera, sizeof(strlen(carrera)), 1, file);
    //printf("%s %s", nombre, nombre_actual);
    while (!feof(file)){
        if (strcmp(nombre_actual, nombre) == 0) {
            counter++;
        }
        //printf("\n%s %s", nombre, nombre_actual);
        fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, file);
        fread(&calificacion, sizeof(float), 1, file);
        fread(&semestre, sizeof(int), 1, file);
        fread(&generacion, sizeof(int), 1, file);
        fread(carrera, sizeof(strlen(carrera)), 1, file);     
    }
    fclose(file);
    return counter;
}

void buscar_alumno_y_eliminar(){
    char nombre[50];
    printf("Ingrese el nombre del alumno que desea modificar: ");
    scanf("%s", nombre);

    int num_alumnos=numero_de_alumnos(nombre);
    char nombre_actual[50], carrera[50];
    
    int generacion, 
        semestre, 
        encontrado = 0, 
        nueva_generacion, 
        nuevo_semestre;
    
    float nueva_calificacion, calificacion;

    FILE *archivo_lectura = fopen("practica2.bin", "rb");
    FILE *archivo_escritura = fopen("temp.bin", "wb");

    if(num_alumnos==1){
        fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
        fread(&calificacion, sizeof(float), 1, archivo_lectura);
        fread(&semestre, sizeof(int), 1, archivo_lectura);
        fread(&generacion, sizeof(int), 1, archivo_lectura);
        fread(carrera, sizeof(strlen(carrera)), 1, archivo_lectura);
        while (!feof(archivo_lectura)) {
            if (!(strcmp(nombre_actual, nombre) == 0)) {
                fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
                fwrite(&calificacion, sizeof(float), 1, archivo_escritura);
                fwrite(&semestre, sizeof(int), 1, archivo_escritura);
                fwrite(&generacion, sizeof(int), 1, archivo_escritura);
                fwrite(carrera, sizeof(strlen(carrera)), 1, archivo_escritura);
            }
            fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
            fread(&calificacion, sizeof(float), 1, archivo_lectura);
            fread(&semestre, sizeof(int), 1, archivo_lectura);
            fread(&generacion, sizeof(int), 1, archivo_lectura);
            fread(carrera, sizeof(strlen(carrera)), 1, archivo_lectura);
        }
        if (encontrado) {
            printf("El alumno ha sido eliminado correctamente.\n");
        } else {
            printf("No se encontro ningún alumno con ese nombre.\n");
        }
    } else if(num_alumnos>1){
        printf("Dame informacion extra.\n");
        printf("Dime el semestre: ");
        scanf("%d", &nuevo_semestre);
        printf("Dime la generacion: ");
        scanf("%d", &nueva_generacion);
        fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
        fread(&calificacion, sizeof(float), 1, archivo_lectura);
        fread(&semestre, sizeof(int), 1, archivo_lectura);
        fread(&generacion, sizeof(int), 1, archivo_lectura);
        fread(carrera, sizeof(strlen(carrera)), 1, archivo_lectura);
        while (!feof(archivo_lectura)) {
            if (!(strcmp(nombre_actual, nombre) == 0 && nueva_generacion == generacion 
                && nuevo_semestre == semestre ) ) {
                fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
                fwrite(&calificacion, sizeof(float), 1, archivo_escritura);
                fwrite(&semestre, sizeof(int), 1, archivo_escritura);
                fwrite(&generacion, sizeof(int), 1, archivo_escritura);
                fwrite(carrera, sizeof(strlen(carrera)), 1, archivo_escritura);
            }
            fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
            fread(&calificacion, sizeof(float), 1, archivo_lectura);
            fread(&semestre, sizeof(int), 1, archivo_lectura);
            fread(&generacion, sizeof(int), 1, archivo_lectura);
            fread(carrera, sizeof(strlen(carrera)), 1, archivo_lectura);
        }
    } else {
        fclose(archivo_lectura);
        fclose(archivo_escritura);
        remove("temp.bin");
        return;
    } 
    fclose(archivo_lectura);
    fclose(archivo_escritura);
    remove("practica2.bin");
    rename("temp.bin", "practica2.bin");
    
}



void modificar(){
    char nombre[50];
    printf("Ingrese el nombre del alumno que desea modificar: ");
    scanf("%s", nombre);

    int num_alumnos=numero_de_alumnos(nombre);
    char nombre_actual[50], carrera[50];
    
    int generacion, 
        semestre, 
        encontrado = 0, 
        nueva_generacion, 
        nuevo_semestre;
    
    float nueva_calificacion, calificacion;
    
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
        fread(carrera, sizeof(strlen(carrera)), 1, archivo_lectura);
        while (!feof(archivo_lectura)) {
            if (strcmp(nombre_actual, nombre) == 0) {
                fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
                fwrite(&nueva_calificacion, sizeof(float), 1, archivo_escritura);
                fwrite(&semestre, sizeof(int), 1, archivo_escritura);
                fwrite(&generacion, sizeof(int), 1, archivo_escritura);
                fwrite(carrera, sizeof(strlen(carrera)), 1, archivo_escritura);
            } else {
                fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
                fwrite(&calificacion, sizeof(float), 1, archivo_escritura);
                fwrite(&semestre, sizeof(int), 1, archivo_escritura);
                fwrite(&generacion, sizeof(int), 1, archivo_escritura);
                fwrite(carrera, sizeof(strlen(carrera)), 1, archivo_escritura);
            }
            fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
            fread(&calificacion, sizeof(float), 1, archivo_lectura);
            fread(&semestre, sizeof(int), 1, archivo_lectura);
            fread(&generacion, sizeof(int), 1, archivo_lectura);
            fread(carrera, sizeof(strlen(carrera)), 1, archivo_lectura);
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
        fread(carrera, sizeof(strlen(carrera)), 1, archivo_lectura);
        while (!feof(archivo_lectura)) {
            if (strcmp(nombre_actual, nombre) == 0 && nueva_generacion == generacion 
                && nuevo_semestre == semestre  ) {
                fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
                fwrite(&nueva_calificacion, sizeof(float), 1, archivo_escritura);
                fwrite(&semestre, sizeof(int), 1, archivo_escritura);
                fwrite(&generacion, sizeof(int), 1, archivo_escritura);
                fwrite(carrera, sizeof(strlen(carrera)), 1, archivo_escritura);
            } else {
                fwrite(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_escritura);
                fwrite(&calificacion, sizeof(float), 1, archivo_escritura);
                fwrite(&semestre, sizeof(int), 1, archivo_escritura);
                fwrite(&generacion, sizeof(int), 1, archivo_escritura);
                fwrite(carrera, sizeof(strlen(carrera)), 1, archivo_escritura);
            }
            fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, archivo_lectura);
            fread(&calificacion, sizeof(float), 1, archivo_lectura);
            fread(&semestre, sizeof(int), 1, archivo_lectura);
            fread(&generacion, sizeof(int), 1, archivo_lectura);
            fread(carrera, sizeof(strlen(carrera)), 1, archivo_lectura);
        }
    } else {
        fclose(archivo_lectura);
        fclose(archivo_escritura);
        remove("temp.bin");
        return;
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

    FILE *file = fopen("practica2.bin", "rb");

    char nombre_actual[50];
    float calificacion;
    int generacion, semestre;
    int encontrado = 0;
    char carrera[50];
    fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, file);
    fread(&calificacion, sizeof(float), 1, file);
    fread(&semestre, sizeof(int), 1, file);
    fread(&generacion, sizeof(int), 1, file);
    fread(carrera, sizeof(strlen(carrera)), 1, file);
    header();
    while (!feof(file)) {
        if (strcmp(nombre_actual, nombre) == 0) {
            print_student(nombre, calificacion, semestre, generacion, carrera);
        }        
        fread(nombre_actual, sizeof(strlen(nombre_actual)), 1, file);
        fread(&calificacion, sizeof(float), 1, file);
        fread(&semestre, sizeof(int), 1, file);
        fread(&generacion, sizeof(int), 1, file);
        fread(carrera, sizeof(strlen(carrera)), 1, file);
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
                add_student();
                break;
            case 2:
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

// Add random students

void add_student_db(){
    char nombres[5][50] = {"Juan", "Mariana", "Palmira", "Loredo", "Pedrito"};
    char carrras[5][50] = {"ISI", "IC", "IEE", "IEA", "IM"};
    FILE *file;
    file = fopen("practica2.bin", "rb+");
    if(file == NULL){
        file = fopen("practica2.bin", "wb+");
    } else 
        fseek(file, 0, SEEK_END);
    char nombre[50];
    float calificacion;
    int semestre;
    int generacion;
    char carrera[50];
    printf("%d", rand() % 5 );
    strcpy(nombre, nombres[rand() % 5 ]);
    strcpy(carrera, carrras[rand() % 5 ]);
    semestre = rand() % 13 ;
    generacion = rand() % 2020 ;
    calificacion = rand() % 101;
    fwrite(nombre, sizeof(strlen(nombre)), 1, file);
    fwrite(&calificacion, sizeof(float), 1, file);
    fwrite(&semestre, sizeof(int), 1, file);
    fwrite(&generacion, sizeof(int), 1, file);
    fwrite(carrera, sizeof(strlen(carrera)), 1, file);
    fclose(file);
}

int main(){
    menu();
    // Create file
    //for(int i=0; i<30; i++)
    //    add_student_db();
}