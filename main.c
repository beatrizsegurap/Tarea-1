#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"


//Creamos la estructura bombero y dia para el horario
typedef struct{
  const char * Rut;
  const char * Name;
  int Disponibilidad[7];
  int Horario[7];
  int diasDisp;
  int trabaja;
}Bombero;

typedef struct{
char nombreD[11];
char rut[5][12];
char name[5][30];
int disp[5];
int lugares;
}dia;


//---------------------------------------------------------------------------
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

void load(FILE *fp, List *B)
{
    // Cadena para guardar la linea completa del archivo csv
    char linea[1024];
    int i;


    int k=0;
    

    while (fgets (linea, 1023, fp) != NULL) { // Se lee la linea
    //Creamos un bombero por linea de archivo y guardamos en el los datos 
        Bombero *bombero = (Bombero*) malloc (sizeof(Bombero));
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
       

        k++; if(k==40) break;
    }

}

void printBomberos(List * B){
    //Imprimimos los bomberos por lo que apuntamos el current a la cabeza de la lista
    Bombero* bActual = firstList(B);
    printf("---------------------------------------------------------------------\n");
    printf("RUT            NOMBRE                     DISPONIBILIDAD\n");
    while(bActual){
        printf("%-10s",bActual->Rut);
        printf("     ");
        printf("%-16s",bActual->Name);
        printf("          ");
        printf("[ %d %d %d %d %d %d %d ]\n",bActual->Disponibilidad[0],bActual->Disponibilidad[1],bActual->Disponibilidad[2],bActual->Disponibilidad[3],bActual->Disponibilidad[4],bActual->Disponibilidad[5],bActual->Disponibilidad[6]);
        bActual=nextList(B);
    }
    printf("---------------------------------------------------------------------\n");
}


//Funcion para importar los bomberos del archivo ingresado por el usuario y retorna la lista con bomberos
List* ImportarBomberos(){
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
    List * B = createList();
    //Cargamos los datos del archivo y creamos las estructuras
    load(file,B);

    
    return B;

}
void agregarBombero(List * B)
{
    //Creamos el bombero nuevo y reservamos memoria para los datos a ingresar
    Bombero * bombero = (Bombero*) malloc (sizeof(Bombero));
    char* rut=(char*) malloc(12*sizeof(char));
    char* name=(char*) malloc(30*sizeof(char));
    printf("---------------------------------------------------------------------\n");
    printf("Ingrese un Rut: ");
    scanf("%s",rut);
    getchar();
    bombero->Rut=rut;

    printf("Ingrese Nombre y Apellido: ");
    scanf("%[^'\n']s",name);
    getchar();
    bombero->Name=name;

    printf("\nEscriba SI o NO segun disponibilidad\n");
    char cad[53] = "Lunes:Martes:Miercoles:Jueves:Viernes:Sabado:Domingo:";
    char disp[3];
    int i,j=0; 
    for(i=0 ; i<53 ; i++)
    {
        printf("%c",cad[i]); 
        if(cad[i] == 58)
        {
            scanf("%s",&disp);
            
            if(strcmp(disp,"SI")==0)
            {
                bombero->Disponibilidad[j]= 1;
                if(j==6)break;
                j++;
            }
            else
            {
                bombero->Disponibilidad[j]= 0;
                if(j==6)break;
                j++;
            }
        }
        
    } 
    pushBack(B,bombero);
    printf("---------------------------------------------------------------------\n");
    printf("\nNuevo bombero agregado con exito\n");
    printf("---------------------------------------------------------------------\n");
}
//Busca un Rut recibido y envia el current del rut encontrado
void *BuscadorPorRut (List * B, char* Rut_ingresado )
{
  Bombero* b=firstList(B);
  while(strcmp(Rut_ingresado,b->Rut)!=0)
  {
      b=nextList(B);
      if(!b)break;
  }
  if(!b)
  {
    printf("El rut escrito, no fue encontrado\n");
    return NULL;
  }
  return b;
}
//Se ingresa un Rut del bombero que se quiere despedir, y elimina al Bombero 
void Eliminarbombero (List *B)
{
  char Rut_ingresado[10];
  Bombero* b;
  printf("Ingrese el Rut del bombero que desea despedir: ");
  scanf("%s",&Rut_ingresado);
  while (strlen(Rut_ingresado)>10 || strlen(Rut_ingresado)<9)
  {
     printf("Rut mal ingresado, Porfavor escriba denuevo\n");
     scanf("%s",&Rut_ingresado);
  }
  b = BuscadorPorRut(B, Rut_ingresado);
  if(b != NULL)
  {
    popCurrent(B);
    printf("---------------------------------------------------------------------\n");
    printf("Bombero Eliminado\n"); 
    printf("---------------------------------------------------------------------\n");
  } 
}
//Es la Interfaz en la cual se ingresa el Rut y redirige a la funcion que busca el rut
void BuscarRut1(List * B)
{  
  char Rut_ingresado[10];
  Bombero* b;
  printf("\nIngrese el Rut de un bombero: ");
  scanf("%s",&Rut_ingresado);
  while (strlen(Rut_ingresado)>10 || strlen(Rut_ingresado)<9)
  {
     printf("Rut mal ingresado, Porfavor escriba denuevo\n");
     scanf("%s",&Rut_ingresado);
  }
  b = BuscadorPorRut(B, Rut_ingresado);
  if(b != NULL)
  {
    printf("---------------------------------------------------------------------\n");
    printf("RUT            NOMBRE                     DISPONIBILIDAD\n");
    printf("%-10s",b->Rut);
    printf("     ");
    printf("%-16s",b->Name);
    printf("          ");
    printf("[ %d %d %d %d %d %d %d ]\n",b->Disponibilidad[0],b->Disponibilidad[1],b->Disponibilidad[2],b->Disponibilidad[3],b->Disponibilidad[4],b->Disponibilidad[5],b->Disponibilidad[6]);
    printf("---------------------------------------------------------------------\n");
  }
}

//Buscamos los bomberos disponibles el dia ingresado

bool buscarDia(List * B, char * dia){
    Bombero *b = firstList(B);
    if(!strcmp(dia,"lunes")){
        printf("---------------------------------------------------------------------\n");
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[0]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        printf("---------------------------------------------------------------------\n");
        return true;
    }
    if(!strcmp(dia,"martes")){
        printf("---------------------------------------------------------------------\n");
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[1]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        printf("---------------------------------------------------------------------\n");
        return true;
    }
    if(!strcmp(dia,"miercoles")){
        printf("---------------------------------------------------------------------\n");
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[2]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        printf("---------------------------------------------------------------------\n");
        return true;
    }
    if(!strcmp(dia,"jueves")){
        printf("---------------------------------------------------------------------\n");
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[3]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        printf("---------------------------------------------------------------------\n");
        return true;
    }
    if(!strcmp(dia,"viernes")){
        printf("---------------------------------------------------------------------\n");
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[4]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        printf("---------------------------------------------------------------------\n");
        return true;
    }
    if(!strcmp(dia,"sabado")){
        printf("---------------------------------------------------------------------\n");
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[5]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        printf("---------------------------------------------------------------------\n");
        return true;
    }
    if(!strcmp(dia,"domingo")){
        printf("---------------------------------------------------------------------\n");
        printf("RUT                   NOMBRE\n");
        do{
           if(b->Disponibilidad[6]==1){
               printf("%s           %s\n",b->Rut,b->Name);
           }
           b = nextList(B);
        }while(b);
        printf("---------------------------------------------------------------------\n");
        return true;
    }
    else{
        printf("---------------------------------------------------------------------\n");
        printf("                    El dia ingresado no es correcto                  \n");
        printf("---------------------------------------------------------------------\n");
        return false;
    }
}
void buscarporDia(List * B){
    char dia[11];
    bool flag=false;
    while(!flag){
        printf("---------------------------------------------------------------------\n");
        printf("Ingrese dia para buscar bomberos disponibles: ");
        scanf("%s",&dia);
        flag = buscarDia(B,dia);
    }
    printf("\n");
}
//--------------------------------------------------------

//Modificaci??n de disponibilidad de bombero seleccionado por rut.
void modificarDisponibilidad(List * B){

    Bombero* b;
    //Se busca un bombero por su rut.
    char Rut_ingresado[10];
    printf("Ingrese el Rut de un bombero: ");
    scanf("%s",&Rut_ingresado);
    while (strlen(Rut_ingresado)>10 || strlen(Rut_ingresado)<9){

     printf("Rut mal ingresado, Porfavor escriba denuevo\n");
     scanf("%s",&Rut_ingresado);
    }

    //Se llama a funcion BuscadorPorRut, devuelve el bombero seleccionado. Si no existe, el programa se devuelve al men??.
    b = BuscadorPorRut(B, Rut_ingresado);
    if(b){

        printf("Modifique disponibilidad del bombero (SI / NO)\n");


        char SiNo[3]; //Guardar los "SI" o "NO"
        int DiasSemana[7]; // Arreglo para guardar 1 y 0 (1=SI, 0=NO)

        /////////////////////
        printf("Lunes, ");
        
        //Se recibe el SI o NO del usuario.
        do{
            printf("Escriba SI o NO\n");
            scanf("%s",&SiNo);
            

        }while(strcmp(SiNo, "SI")!= 0 && strcmp(SiNo, "NO") != 0);

        //Se guarda la opcion SI o NO.
        if(!strcmp(SiNo,"SI")){ 
            DiasSemana[0] = 1;
        }else{
            DiasSemana[0] = 0;
        }

        /////////////////////

        printf("Martes, ");

        do{
            printf("Escriba SI o NO\n");
            scanf("%s",&SiNo);
            

        }while(strcmp(SiNo, "SI")!= 0 && strcmp(SiNo, "NO") != 0);

        if(!strcmp(SiNo,"SI")){ 
            DiasSemana[1] = 1;
        }else{
            DiasSemana[1] = 0;
        }

        /////////////////////

        printf("Miercoles, ");

        do{
            printf("Escriba SI o NO\n");
            scanf("%s",&SiNo);
            

        }while(strcmp(SiNo, "SI")!= 0 && strcmp(SiNo, "NO") != 0);

        if(!strcmp(SiNo,"SI")){ 
            DiasSemana[2] = 1;
        }else{
            DiasSemana[2] = 0;
        }

        /////////////////////

        printf("Jueves, ");

        do{
            printf("Escriba SI o NO\n");
            scanf("%s",&SiNo);
            

        }while(strcmp(SiNo, "SI")!= 0 && strcmp(SiNo, "NO") != 0);

        if(!strcmp(SiNo,"SI")){ 
            DiasSemana[3] = 1;
        }else{
            DiasSemana[3] = 0;
        }

        /////////////////////

        printf("Viernes, ");

        do{
            printf("Escriba SI o NO\n");
            scanf("%s",&SiNo);
            

        }while(strcmp(SiNo, "SI")!= 0 && strcmp(SiNo, "NO") != 0);

        if(!strcmp(SiNo,"SI")){ 
            DiasSemana[4] = 1;
        }else{
            DiasSemana[4] = 0;
        }

        /////////////////////

        printf("Sabado, ");

        do{
            printf("Escriba SI o NO\n");
            scanf("%s",&SiNo);
            

        }while(strcmp(SiNo, "SI")!= 0 && strcmp(SiNo, "NO") != 0);

        if(!strcmp(SiNo,"SI")){ 
            DiasSemana[5] = 1;
        }else{
            DiasSemana[5] = 0;
        }

        /////////////////////

        printf("Domingo, ");

        do{
            printf("Escriba SI o NO\n");
            scanf("%s",&SiNo);
            

        }while(strcmp(SiNo, "SI")!= 0 && strcmp(SiNo, "NO") != 0);

        if(!strcmp(SiNo,"SI")){ 
            DiasSemana[6] = 1;
        }else{
            DiasSemana[6] = 0;
        }

        /////////////////////
        
        //Se guardan los dias de disponibilidad en el bombero seleccionado.
        b->Disponibilidad[0] = DiasSemana[0];
        b->Disponibilidad[1] = DiasSemana[1];
        b->Disponibilidad[2] = DiasSemana[2];
        b->Disponibilidad[3] = DiasSemana[3];
        b->Disponibilidad[4] = DiasSemana[4];
        b->Disponibilidad[5] = DiasSemana[5];
        b->Disponibilidad[6] = DiasSemana[6];

        printf("\n - Cambios de disponibilidad realizados correctamente - \n\n");
    }

}


List* crearHorario(List* B){
    //creamos la lista del horario
    List* H=createList();
    //memoria y el nombre para cada uno de los dias.
    dia* lunes=(dia*)malloc(sizeof(dia));
    strcpy(lunes->nombreD,"Lunes");
    dia* martes=(dia*)malloc(sizeof(dia));
    strcpy(martes->nombreD,"Martes");
    dia* miercoles=(dia*)malloc(sizeof(dia));
    strcpy(miercoles->nombreD,"Miercoles");
    dia* jueves=(dia*)malloc(sizeof(dia));
    strcpy(jueves->nombreD,"Jueves");
    dia* viernes=(dia*)malloc(sizeof(dia));
    strcpy(viernes->nombreD,"Viernes");
    dia* sabado=(dia*)malloc(sizeof(dia));
    strcpy(sabado->nombreD,"Sabado");
    dia* domingo=(dia*)malloc(sizeof(dia));
    strcpy(domingo->nombreD,"Domingo");
    //a??adimos los dias a la lista.
    pushFront(H,lunes);
    pushBack(H,martes);
    pushBack(H,miercoles);
    pushBack(H,jueves);
    pushBack(H,viernes);
    pushBack(H,sabado);
    pushBack(H,domingo);
    //variables para los ciclos
    dia* aux=(dia*)malloc(sizeof(dia));
    Bombero* bomberoaux=(Bombero*)malloc(sizeof(Bombero));
    bomberoaux=firstList(B);
    int i,j,p,d;//i es un contador para ciclos, j lo mismo, p es para la posicion
    while(bomberoaux != NULL){
        bomberoaux->trabaja=0;
        bomberoaux=nextList(B);
        if(!bomberoaux)break;
    }

    //Este ciclo pasara por todos los dias de la semana del horario generandolos
    aux=firstList(H);
    for(i=0; i<=6 ;i++){
        bomberoaux=firstList(B);
        //lugares es una variable que nos dira cuantos bomberos ya tenemos asignados para dicho dia,permitiendo remplazarlos o avisar si no hay suficientes una vez generado el horario
        aux->lugares=0;
        while(bomberoaux != NULL){
        //pasara por toda la lista
            if(bomberoaux->Disponibilidad[i]==1&& bomberoaux->trabaja<5){
            //si el bombero tiene disponibilidad entrara
                if(aux->lugares<5){
                //Si el dia no esta completo lo a??ade altiro
                    strcpy(aux->name[aux->lugares],bomberoaux->Name);
                    //printf("%s",aux->name[aux->lugares]);
                    strcpy(aux->rut[aux->lugares],bomberoaux->Rut);
                    //printf("%s",aux->rut[aux->lugares]);
                    aux->disp[aux->lugares]=bomberoaux->diasDisp;
                    aux->lugares+=1;
                    bomberoaux->trabaja+=1;
                }//------------------------------------------------------
                /*else{//encaso de que el dia este completo, compara todos los bomberos basandose en sus dias de disponibilidad con el resto priorizando a los bomberos con menor tiempo disponible
                    d=bomberoaux->diasDisp;
                    //para comparar disponibilidad
                    p=0;
                    //Esta variable guarda la posicion en la cual, se encuentra almacenado el bombero de turno que sera remplazado
                    for(j=0;j<5;j++){
                        if(d < aux->disp[j]){
                            d=aux->disp[j];
                            p=j;
                        }
                    }	
                }
                if(p != 0){
                    strcpy(aux->name[p],bomberoaux->Name);
                    strcpy(aux->rut[p],bomberoaux->Rut);
                }*/	//---------------------------------------------------------
            }
            //Termina el scaneo por la lista una vez se llega al ultimo dato.
            bomberoaux=nextList(B);
            if(!bomberoaux)break;
            //pasa al siguiente bombero.
        }
        aux=nextList(H);
    }
    printf("---------------------------------------------------------------------\n");
    printf("                   SE CREO EL HORARIO EXITOSAMENTE                   \n");
    printf("---------------------------------------------------------------------\n");
    return H;// Devuelve un puntero al horario que se guardara en main.
}

void mostrarHorario(List* H){
    printf("---------------------------------------------------------------------\n");
    if(!H)printf("Aun no se ha creado un horario\n---------------------------------------------------------------------\n");
    else{
        printf("El horario de esta semana es:\n");
        dia* diaux=(dia*)malloc(sizeof(dia));
        diaux=firstList(H);
        int i,x,z;//i es para el contador del ciclo, x sera una variable la cual nos dira cuantos bomberos no estan disponibles
        for(i=0;i<=6;i++){
            printf("---------------------------------------------------------------------\n");
            printf("                              %s                          \n",diaux->nombreD);
            printf("---------------------------------------------------------------------\n");
            printf("RUT            NOMBRE\n");
            for(z=0;z<diaux->lugares;z++){
                printf("%-10s",diaux->rut[z]);
                printf("     ");
                printf("%-16s\n",diaux->name[z]);
            }
            if(diaux->lugares<5){
                for(x=4-diaux->lugares;x+z<=3;x++){
                    printf("-No hay suficiente personal disponible\n");
                }
            }
            printf("\n");
            diaux=nextList(H);
        }
    }
}

//---------------------------------------------------------------------------


//Funcion principal main con el menu

int main()
{
    List* B;
    //Importamos los bomberos desdeun archivo csv
    B=ImportarBomberos();
    int op=1;
    List* H=NULL;
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
        printf("7. Mostrar horario semanal\n");
        printf("8. Mostrar todos los bomberos\n");
        printf("0. Salir\n");
        scanf("%d", &op);

        switch(op)
        {
            case 1:agregarBombero(B);break;
            case 2:Eliminarbombero(B);break;
            case 3:buscarporDia(B);break;
            case 4:BuscarRut1(B);break;
            case 5:modificarDisponibilidad(B);break;
            case 6:H=crearHorario(B);break;
            case 7:mostrarHorario(H);break;
            case 8:printBomberos(B);break;
        }
    }
    

    return 0;
}
