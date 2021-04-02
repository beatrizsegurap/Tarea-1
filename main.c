#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.c"

int main()
{
    char nameFile[101];
    FILE *file;
    //Abrimos el archivo ingresado por el usuario
    do{
        printf("Ingrese el nombre del archivo con extension: ");
        scanf("%s",&nameFile);
        file = fopen (nameFile, "r" ); 
    }while(!file);

    //Cargamos los datos del archivo y creamos las estructuras
    load(file);
    

    return 0;
}
