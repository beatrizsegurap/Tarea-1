#include <stdio.h>
#include <stdlib.h>
//#include "list.h"
#include "list.c"

//Funcion para leer el k-esimo elemento de un string (separado por comas)
const char*get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc(100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

void load(FILE *fp, ListBomberos *B)
{
    // Cadena para guardar la linea completa del archivo csv
    char linea[1024];
    int i;


    int k=0;
    

    while (fgets (linea, 1023, fp) != NULL) { // Se lee la linea
    //Creamos un bombero por linea de archivo y guardamos en el los datos 
        Bombero *bombero = createBombero();
        int dia=0, frecuencia=0;
        for(i=0;i<9;i++){
            const char *aux = get_csv_field(linea, i); 
            //Guardamos el Rut
            if(i==0){
                bombero->Rut=(char*)aux;
            }
            //Guardamos el nombre
            if(i==1){
                bombero->Name=(char*)aux;
                
            }
            //Guardamos la disponibilidad
            if(i>=2){
                if(!strcmp(aux,"SI")){
                    bombero->Disponibilidad[dia]=1;
                    frecuencia+=1;
                }
                else{
                    bombero->Disponibilidad[dia]=0;
                }
                dia+=1;               
            }
            //guardamos la cantidad de dias a la semana que el bombero tiene disponibilidad
            bombero->diasDisp=frecuencia;
        }

        //Si es el primer bombero a agregar entonces lo agregamos al inicio y actualizamos el current de lo contrario lo agregamos al final de la lista
        if(!B->Head){
            pushFront(B,bombero);
            B->Current=B->Head;
        }
        else{
            pushBack(B,bombero);
        }
       

        printf("\n");
        k++; if(k==20) break;
    }

}

void printBomberos(ListBomberos * B){
    //Imprimimos los bomberos por lo que apuntamos el current a la cabeza de la lista
    firstList(B);
    printf("RUT            NOMBRE                     DISPONIBILIDAD\n");
    while(B->Current!=B->Tail){
        printf("%-10s",B->Current->Rut);
        printf("     ");
        printf("%-16s",B->Current->Name);
        printf("          ");
        printf("[ %d %d %d %d %d %d %d ]\n",B->Current->Disponibilidad[0],B->Current->Disponibilidad[1],B->Current->Disponibilidad[2],B->Current->Disponibilidad[3],B->Current->Disponibilidad[4],B->Current->Disponibilidad[5],B->Current->Disponibilidad[6]);
        B->Current=B->Current->Next;
    }

    //Imprimimos el ultimo
    printf("%-10s",B->Tail->Rut);
    printf("     ");
    printf("%-16s",B->Tail->Name);
    printf("          ");
    printf("[ %d %d %d %d %d %d %d ]\n",B->Tail->Disponibilidad[0],B->Tail->Disponibilidad[1],B->Tail->Disponibilidad[2],B->Tail->Disponibilidad[3],B->Tail->Disponibilidad[4],B->Tail->Disponibilidad[5],B->Tail->Disponibilidad[6]);
}

void ImportarBomberos(){
    char nameFile[101];
    FILE *file;

    //Abrimos el archivo ingresado por el usuario
    do{
        printf("Ingrese el nombre del archivo sin extension: ");
        scanf("%s",&nameFile);
        strcat(nameFile,".csv");
        file = fopen (nameFile, "r" ); 
    }while(!file);


    //Creamos la lista con bomberos
    ListBomberos * B = createListBomberos();
    //Cargamos los datos del archivo y creamos las estructuras
    load(file,B);

    printBomberos(B);

}
