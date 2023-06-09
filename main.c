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

void write_file(FILE *file, char name[50], 
                float grade, int semester, 
                int gen, char career[50]);
void read_file(FILE *file, char name[50], 
                float *grade, int *semester, 
                int *gen, char career[50]);
void add_student();
void header();
void print_student(
                    char nombre[50], float calificacion,
                    int semestre, int generacion,
                    char carrera[50]
                );

void prints_list();
void buscar_alumno_y_eliminar();
void modificar();
void buscar_alumno_y_mostrar();
void menu();
void add_student_db();
void data_description();
void description();
int menu_opciones();
int numero_de_alumnos(char nombre[]);

void sort(){
    
}

int main(){
    description();
    menu();
    // Create file
    //for(int i=0; i<30; i++)
    //    add_student_db();
}

void write_file(FILE *file, char name[50], float grade, int semester, int gen, char career[50]){
    fwrite(name, sizeof(strlen(name)), 1, file);
    fwrite(&grade, sizeof(float), 1, file);
    fwrite(&semester, sizeof(int), 1, file);
    fwrite(&gen, sizeof(int), 1, file);
    fwrite(career, sizeof(strlen(career)), 1, file);
}

void read_file(FILE *file, char name[50], float *grade, int *semester, int *gen, char career[50]){
    fread(name, sizeof(strlen(name)), 1, file);
    fread(grade, sizeof(float), 1, file);
    fread(semester, sizeof(int), 1, file);
    fread(gen, sizeof(int), 1, file);
    fread(career, sizeof(strlen(career)), 1, file);
}

void add_student(){
    FILE *archivo_lectura;
    archivo_lectura = fopen("practica2.bin", "rb");
    FILE *archivo_escritura = fopen("temp.bin", "wb");
    char nombre_n[50];
    float calificacion_n;
    int semestre_n;
    int generacion_n;
    char carrera_n[50];
    printf("Dime el nombre: ");
    scanf("%s", nombre_n);
    printf("Dime la calificacion: ");
    scanf("%f", &calificacion_n);
    printf("Dime el semestre: ");
    scanf("%d", &semestre_n);
    printf("Dime la generacion: ");
    scanf("%d", &generacion_n);
    printf("Dime la carrera: ");
    scanf("%s", carrera_n);
    int bandera=0;
    char nombre_actual[50], carrera[50];
    int generacion, 
        semestre, 
        encontrado = 0, 
        nueva_generacion, 
        nuevo_semestre;
    
    float calificacion;
    
    float nueva_calificacion=0;

    read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
    
    while (!feof(archivo_lectura)) {
        if (strcmp(nombre_actual, nombre_n) > 0 && bandera==0) {
            write_file(archivo_escritura, nombre_n, calificacion_n, semestre_n, generacion_n, carrera_n);
            write_file(archivo_escritura, nombre_actual, calificacion, semestre, generacion, carrera);
            bandera=1;
        } else {
            write_file(archivo_escritura, nombre_actual, calificacion, semestre, generacion, carrera);
        }
        read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
    }
    if(bandera==0){
        write_file(archivo_escritura, nombre_n, calificacion_n, semestre_n, generacion_n, carrera_n);
    }
    fclose(archivo_lectura);
    fclose(archivo_escritura);
    remove("practica2.bin");
    rename("temp.bin", "practica2.bin");
}

void header(){
    FILE *file;
    file = fopen("diccionario.txt", "r");
    char text[100], aux[100];
    fgets(text, sizeof(text), file);
    for(int i=0; i<128; i++)
        printf("-");
    printf("\n");
    while(!feof(file)){
        fgets(text, sizeof(text), file);
        char *ptr; 
        ptr = strtok(text, " ");  
        printf("|");
        for(int i=0; i<8; i++)
            printf(" ");
        printf("%s", ptr);
        for(int i=0; i<8; i++)
            printf(" ");
        strtok (NULL, " ");
        strtok (NULL, " ");
        strtok (NULL, " ");
    }
    printf("|\n");
    for(int i=0; i<128; i++)
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
    printf("|%-22s|%-28.2f|%-23s|%-24d|%-26d|\n", nombre, calificacion, carrera, semestre, generacion);
    for(int i=0; i<128; i++)
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
    
    read_file(file, nombre, &calificacion, &semestre, &generacion, carrera);
    
    header();
    while(!feof(file)){
        print_student(nombre, calificacion, semestre, generacion, carrera);
        read_file(file, nombre, &calificacion, &semestre, &generacion, carrera);
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
    
    read_file(file, nombre_actual, &calificacion, &semestre, &generacion, carrera);
    
    while (!feof(file)){
        if (strcmp(nombre_actual, nombre) == 0) {
            counter++;
        }
        read_file(file, nombre_actual, &calificacion, &semestre, &generacion, carrera);     
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
        eliminado = 0, 
        nueva_generacion, 
        nuevo_semestre;
    
    float nueva_calificacion, calificacion;

    FILE *archivo_lectura = fopen("practica2.bin", "rb");
    FILE *archivo_escritura = fopen("temp.bin", "wb");

    if(num_alumnos==1){
        read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
        while (!feof(archivo_lectura)) {
            if (!(strcmp(nombre_actual, nombre) == 0)) {
                write_file(archivo_escritura, nombre_actual, calificacion, semestre, generacion, carrera);
                eliminado++;
            }
            read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
        }
    } else if(num_alumnos>1){
        printf("Dame informacion extra.\n");
        printf("Dime el semestre: ");
        scanf("%d", &nuevo_semestre);
        printf("Dime la generacion: ");
        scanf("%d", &nueva_generacion);
        read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
        
        while (!feof(archivo_lectura)) {
            if (!(strcmp(nombre_actual, nombre) == 0 && nueva_generacion == generacion 
                && nuevo_semestre == semestre ) ) {
                write_file(archivo_escritura, nombre_actual, calificacion, semestre, generacion, carrera);
                eliminado++;
            }
            read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
        }
    } else {    
        printf("No se encontro ningún alumno con ese nombre.\n");
        fclose(archivo_lectura);
        fclose(archivo_escritura);
        remove("temp.bin");
        return;
    } 
    if(eliminado)
        printf("El alumno ha sido eliminado correctamente.\n");
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
        read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
        
        while (!feof(archivo_lectura)) {
            if (strcmp(nombre_actual, nombre) == 0) {
                write_file(archivo_escritura, nombre_actual, nueva_calificacion, semestre, generacion, carrera);
            } else {
                write_file(archivo_escritura, nombre_actual, calificacion, semestre, generacion, carrera);
            }
            read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
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
        read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
        
        while (!feof(archivo_lectura)) {
            if (strcmp(nombre_actual, nombre) == 0 && nueva_generacion == generacion 
                && nuevo_semestre == semestre  ) {
                write_file(archivo_escritura, nombre_actual, nueva_calificacion, semestre, generacion, carrera);
            } else {
                write_file(archivo_escritura, nombre_actual, calificacion, semestre, generacion, carrera);
            }
            read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
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
    read_file(file, nombre_actual, &calificacion, &semestre, &generacion, carrera);
    header();
    while (!feof(file)) {
        if (strcmp(nombre_actual, nombre) == 0) {
            print_student(nombre, calificacion, semestre, generacion, carrera);
        }    
        read_file(file, nombre_actual, &calificacion, &semestre, &generacion, carrera);    
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
        printf("6. Imprimir ordenados \n");
        printf("7. Salir\n");
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
                prints_list();
            break;
            case 7:
                exit(EXIT_SUCCESS); // Sale del programa
            default:
                printf("Opcion invalida\n");
        }
    }
}

// Add random students

void add_student_db(){
    char nombres[][50] = {"Ana", "Patricio", "Erick", "Mariana", "Maria", "Juan", "Pedro"};
    char carrras[][50] = {"ISI", "IC", "IEE", "IEA", "IM", "IA", "IQ"};
    
    FILE *archivo_lectura;
    archivo_lectura = fopen("practica2.bin", "rb");
    FILE *archivo_escritura = fopen("temp.bin", "wb");
    char nombre_n[50];
    float calificacion_n;
    int semestre_n;
    int generacion_n;
    char carrera_n[50];
    
    int bandera=0;
    char nombre_actual[50], carrera[50];
    int generacion, 
        semestre, 
        encontrado = 0, 
        nueva_generacion, 
        nuevo_semestre;
    
    float calificacion;
    
    float nueva_calificacion=0;
    strcpy(nombre_n, nombres[rand() % 6]);
    strcpy(carrera_n, carrras[rand() % 6 ]);
    semestre_n = rand() % 13 ;
    generacion_n = rand() % 2020 ;
    calificacion_n = rand() % 100;
    read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
    
    while (!feof(archivo_lectura)) {
        if (strcmp(nombre_actual, nombre_n) > 0 && bandera==0) {
            write_file(archivo_escritura, nombre_n, calificacion_n, semestre_n, generacion_n, carrera_n);
            write_file(archivo_escritura, nombre_actual, calificacion, semestre, generacion, carrera);
            bandera=1;
        } else {
            write_file(archivo_escritura, nombre_actual, calificacion, semestre, generacion, carrera);
        }
        read_file(archivo_lectura, nombre_actual, &calificacion, &semestre, &generacion, carrera);
    }
    if(bandera==0){
        write_file(archivo_escritura, nombre_n, calificacion_n, semestre_n, generacion_n, carrera_n);
    }
    fclose(archivo_lectura);
    fclose(archivo_escritura);
    remove("practica2.bin");
    rename("temp.bin", "practica2.bin");
}

void data_description(){
    FILE *file;
    file = fopen("diccionario.txt", "r");
    char text[200];
    fgets(text, 200, file);
    printf("%s", text);
}

void description(){
    FILE *file;
    file = fopen("diccionario.txt", "r");
    char text[200];
    fgets(text, 200, file);
    printf("%s", text);
}