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
        if(vacio(B)){
            pushFront(B,bombero);
            firstList(B);
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
    Bombero* bActual = firstList(B);

    printf("RUT            NOMBRE                     DISPONIBILIDAD\n");
    while(bActual){
        printf("%-10s",bActual->Rut);
        printf("     ");
        printf("%-16s",bActual->Name);
        printf("          ");
        printf("[ %d %d %d %d %d %d %d ]\n",bActual->Disponibilidad[0],bActual->Disponibilidad[1],bActual->Disponibilidad[2],bActual->Disponibilidad[3],bActual->Disponibilidad[4],bActual->Disponibilidad[5],bActual->Disponibilidad[6]);
        bActual=nextList(B);
    }
}


//Funcion para importar los bomberos del archivo ingresado por el usuario y retorna la lista con bomberos
ListBomberos* ImportarBomberos(){
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

    
    return B;

}
void Agregardato(ListBomberos * dato)
{
    Bombero * nuevoDato = createBombero();
    printf("Ingrese un Rut:");
    scanf("%s",&nuevoDato->Rut);
    printf("\nIngrese Nombre y Apellido:");
    scanf("%s",&nuevoDato->Name);
    printf("\nEscriba SI o NO segun disponibilidad\n");
    char cad[53] = "Lunes:Martes:Miercoles:Jueves:Viernes:Sabado:Domingo:";
    char disp[3];
    int i,j=0;
    for(i=0 ; i<53 ; i++)
    {
        printf("%c",cad[i]); 
        if(cad[i]== ':')
        {
            scanf("%s",&disp);
            if(strcmp(disp,"SI")==0)
            {
                nuevoDato->Disponibilidad[j]= 1;
                if(j==7)break;
                j++;
            }
            if(strcmp(disp,"NO")==0)
            {
                nuevoDato->Disponibilidad[j]= 0;
                if(j==7)break;
                j++;
            }
            printf("\n");
        }
    }
    pushBack(dato,nuevoDato);
    printf("Nuevo dato agregado con exito");
}
//Busca un Rut recibido y envia el current del rut encontrado
void *BuscadorPorRut (ListBomberos * bombero, char* Rut_ingresado )
{
  bombero->Current = bombero->Head;
  while(strcmp(Rut_ingresado,bombero->Current->Rut)!=0 && bombero->Current->Next != NULL)
  {
    bombero->Current = bombero->Current->Next;
  }
  if(strcmp(Rut_ingresado,bombero->Current->Rut)!=0)
  {
    printf("El rut escrito, no fue encontrado\n");
    return NULL;
  }
  return bombero->Current;
}
//Se ingresa un Rut del bombero que se quiere despedir, y elimina al Bombero 
void Eliminarbombero (ListBomberos *bombero)
{
  char Rut_ingresado[10];
  printf("Ingrese el Rut del bombero que desea despedir: ");
  scanf("%s",&Rut_ingresado);
  while (strlen(Rut_ingresado)>10 || strlen(Rut_ingresado)<9)
  {
     printf("Rut mal ingresado, Porfavor escriba denuevo\n");
     scanf("%s",&Rut_ingresado);
  }
  bombero->Current = BuscadorPorRut(bombero, Rut_ingresado);
  if(bombero->Current != NULL)
  {
    popCurrent(bombero);
    printf("Bombero Eliminado\n"); 
  } 
}
//Es la Interfaz en la cual se ingresa el Rut y redirige a la funcion que busca el rut
void BuscarRut1(ListBomberos * bombero)
{  
  char Rut_ingresado[10];
  printf("Ingrese el Rut de un bombero: ");
  scanf("%s",&Rut_ingresado);
  while (strlen(Rut_ingresado)>10 || strlen(Rut_ingresado)<9)
  {
     printf("Rut mal ingresado, Porfavor escriba denuevo\n");
     scanf("%s",&Rut_ingresado);
  }
  bombero->Current = BuscadorPorRut(bombero, Rut_ingresado);
  if(bombero->Current != NULL)
  {
    printf("RUT: %s\nNOMBRE: %s\nDISPONIBILIDAD: ",bombero->Current->Rut,bombero->Current->Name);
    printf("[ %d %d %d %d %d %d %d ]\n",bombero->Current->Disponibilidad[0],bombero->Current->Disponibilidad[1],bombero->Current->Disponibilidad[2],bombero->Current->Disponibilidad[3],bombero->Current->Disponibilidad[4],bombero->Current->Disponibilidad[5],bombero->Current->Disponibilidad[6]);

  }
}

//Buscamos los bomberos disponibles el dia ingresado

int buscarDia(ListBomberos * B, char * dia){
    Bombero *b = firstList(B);
    if(!strcmp(dia,"lunes")){
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[0]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        return 1;
    }
    if(!strcmp(dia,"martes")){
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[1]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        return 1;
    }
    if(!strcmp(dia,"miercoles")){
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[2]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        return 1;
    }
    if(!strcmp(dia,"jueves")){
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[3]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        return 1;
    }
    if(!strcmp(dia,"viernes")){
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[4]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        return 1;
    }
    if(!strcmp(dia,"sabado")){
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[5]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        return 1;
    }
    if(!strcmp(dia,"domingo")){
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[6]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        return 1;
    }
    else{
        printf("El dia ingresado no es correcto\n");
        return 0;
    }
}
void buscarporDia(ListBomberos * B){
    char dia[11];
    int flag=0;
    while(flag==0){
        printf("Ingrese dia para buscar bomberos disponibles: ");
        scanf("%s",&dia);
        flag = buscarDia(B,dia);
    }
}