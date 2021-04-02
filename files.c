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


void load(FILE *fp)
{
    // Cadena para guardar la linea completa del archivo csv
    char linea[1024];
    int i;


    int k=0;
    
    //Creamos la lista con bomberos
    ListBomberos * B = (ListBomberos*)malloc(sizeof(ListBomberos));

    while (fgets (linea, 1023, fp) != NULL) { // Se lee la linea
    //Creamos un bombero por linea de archivo y guardamos en el los datos 
        Bombero *bombero = createBombero();
        int dia=0;
        for(i=0;i<9;i++){
            const char *aux = get_csv_field(linea, i); 
            //Guardamos el Rut
            if(i==0){
                bombero->Rut=(char*)aux;
             printf("Rut: %s\n",bombero->Rut);
            }
            //Guardamos el nombre
            if(i==1){
                bombero->Name=(char*)aux;
                
            }
            //Guardamos la disponibilidad
            if(i>=2){
                if(!strcmp(aux,"SI")){
                    bombero->Disponibilidad[dia]=1;
                }
                else{
                    bombero->Disponibilidad[dia]=0;
                }
                printf("dia %d: %d\n",dia,bombero->Disponibilidad[dia]);
                dia+=1;               
            }

        }

        printf("\n");
        k++; if(k==20) break;
    }

}
