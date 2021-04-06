#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.c"

int main()
{
    ListBomberos* B;
    //Importamos los bomberos desdeun archivo csv
    B=ImportarBomberos();
    int op=1;

//MENU
    printf("************ESTACION DE BOMBEROS************\n\n");
    while(op!=0)
    {
        printf("1. Agregar bombero\n");
        printf("2. Despedir bombero\n");
        printf("3. Buscar bombero por dia\n");
        printf("4. Buscar bombero por rut\n");
        printf("5. Modificar disponibilidad de un bombero\n");
        printf("6. Crear horario de la semana\n");
        printf("7. Mostrar todos los bomberos\n");
        printf("0. Salir\n");
        scanf("%d", &op);
        printf("\n");
        switch(op)
        {
            case 1:Agregardato(B);break;
            case 2:Eliminarbombero(B);break;
            case 3:printf("no implementada\n");break;
            case 4:BuscarRut1(B);break;
            case 5:printf("no implementada\n");break;
            case 6:printf("no implementada\n");break;
            case 7:printBomberos(B);break;
        }
    }
    

    return 0;
}
