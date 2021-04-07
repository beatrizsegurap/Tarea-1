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
    Bombero *nuevoDato = createBombero();
    printf("Ingrese un Rut:");
    scanf("%s",nuevoDato->Rut);
    printf("\nIngrese Nombre y Apellido:");
    scanf("%s",nuevoDato->Name);
    printf("\nEscriba SI o NO segun disponibilidad\n");
    char cad[38] = "Lunes:Martes:Miercoles:Jueves:Viernes:";
    char disp[3];
    int i,j=0;
    for(i=0 ; i<39 ; i++)
    {
        printf("%c",cad[i]); 
        if(cad[i]== ':')
        {
            scanf("%s",disp);
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
    printf("El rut escrito, no fue encontrado");
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

/*void AgregarBombero(ListBomberos * B){
    Bombero *bombero = createBombero();
    char name[20],rut[10];
    char* disp[10];
    int i;
    printf("Ingrese rut: ");
    scanf("%s",&rut);
    bombero->Rut=rut;
    printf("Ingrese nombre: ");
    scanf("%s",&name);
    printf("Escriba SI o NO segun disponibilidad\n");
    printf("Lunes: ");
    scanf("%s",&disp[0]);
    printf("Martes: ");
    scanf("%s",&disp[1]);
    printf("Miercoles: ");
    scanf("%s",&disp[2]);
    printf("Jueves: ");
    scanf("%s",&disp[3]);
    printf("Viernes: ");
    scanf("%s",&disp[4]);
    printf("Sabado: ");
    scanf("%s",&disp[5]);
    printf("Domingo: ");
    scanf("%s",&disp[6]);
    for(i=0;i<7;i++){
        if(!strcmp(disp[i],"SI")){
            bombero->Disponibilidad[i]=1;
        }
        else{
            bombero->Disponibilidad[i]=0;
        }
    }
    pushBack(B,bombero);
    printf("El bombero fue agregado con exito\n");

}*/
