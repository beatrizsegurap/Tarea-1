
#include <string.h>
#include <assert.h>
#include <stdbool.h>
//#include "list.h"


/*
  constants
*/
#undef TRUE
#define TRUE 1

#undef FALSE
#define FALSE 0


/*
  type definitions
*/
#undef Boolean
#define Boolean short unsigned int

#undef Object
#define Object void*



/*
  structures
*/

typedef struct Bombero Bombero;
//Creamos la estructura bombero
struct Bombero{
  const char * Rut;
  const char * Name;
  int Disponibilidad[7];
  int Horario[7];
  int diasDisp;
  Bombero * Next;
  Bombero * Prev;
};

typedef struct ListBomberos ListBomberos;

//Creamos una lista de bomberos

struct ListBomberos{
  Bombero * Head;
  Bombero * Current;
  Bombero * Tail;
};

/*
  private function declarations
*/

//Creamos un bombero y retornamos la estructura inicializada
Bombero * createBombero() {
    Bombero * new = (Bombero *)malloc(sizeof(Bombero));
    assert(new != NULL);
    new->Rut = NULL;
    new->Name = NULL;
    new->Prev = NULL;
    new->Next = NULL;
    return new;
}


//Creamos una lista de bomberos y la retornamos inicializada
ListBomberos * createListBomberos() {
    ListBomberos *lista = malloc(sizeof(ListBomberos));
    lista->Head = NULL;
    lista->Tail = NULL;
    lista->Current = NULL;
    
     return lista;
}

struct Horario {
char dia[11];
char rut[5][12];
char name[5][30];
int disp[5];
int lugares;
};

Horario* crearHorario(Listbomberos* B){
int=i,j,p,d;//i es un contador para ciclos, j lo mismo, p es para la posicion
Bombero* bomberoaux=createBombero;
Horario* horario[7];
strcopy(horario[0]->dia,"Lunes");
strcopy(horario[1]->dia,"Martes");
strcopy(horario[2]->dia,"Miercoles");
strcopy(horario[3]->dia,"Jueves");
strcopy(horario[4]->dia,"Viernes");
strcopy(horario[5]->dia,"Sabado");
strcopy(horario[6]->dia,"Domingo");
int=i,j,p,d;
//Este ciclo pasara por todos los dias de la semana del horario generandolos
for(i=0,i<=6,i++){
  bomberoaux=firstList(B);
//lugares es una variable que nos dira cuantos bomberos ya tenemos asignados para dicho dia,permitiendo remplazarlos o avisar si no hay suficientes una vez generado el horario
  horario[i]->lugares=0;
  while(bomberoaux != NULL){
  //pasara por toda la lista
	  if(bomberoaux->Disponibilidad[i]==1){
      //si el bombero tiene disponibilidad entrara
		  if(horario[i]->lugares<4){
        //Si el dia no esta completo lo añade altiro
			  strcpy(horario[i]->rut[horario[i]->lugares],bomberoaux->rut);
			  strcpy(horario[i]->name[horario[i]->lugares],bomberoaux->name);
			  horario[i]->disp[horario[i]->lugares]=bomberoaux->diasDisp;
			  horario[i]->lugares+=1;
			  }
		    else{//encaso de que el dia este completo, compara todos los bomberos basandose en sus dias de disponibilidad con el resto priorizando a los bomberos con menor tiempo disponible
			    d=bomberoaux->diasDisp;
          //para comparar disponibilidad
			    p=0;
          //Esta variable guarda la posicion en la cual, se encuentra almacenado el bombero de turno que sera remplazado
			    for(j=0;j<5;j++){
				    if(d < horario[i]->disp[j]){
					  d=horario[i]->disp[j];
					  p=j;
					  }
			    }	
        }
      if(p != 0){
				strcpy(horario[i]->rut[p],bomberoaux->rut);
				strcpy(horario[i]->name[p],bomberoaux->name);
			}	
	  if(bomberoaux->next==NULL)Break;
//Termina el scaneo por la lista una vez se llega al ultimo dato.
	bomberoaux=nextList(B);
//pasa al siguiente bombero.
	}
}
}
return *horario;// Devuelve un puntero al horario que se guardara en main.
}




// Funciones del TDA a implementar

void * firstList(ListBomberos * list) {
    if(!list->Head)return NULL;
    list->Current=list->Head;
    return list->Current;
}

void * nextList(ListBomberos * list) {
    if(!list->Current)return NULL;
    if(!list->Current->Next)return NULL;
    list->Current=list->Current->Next;
    return list->Current;
}

void * lastList(ListBomberos * list) {
    if(!list->Tail)return NULL;
    list->Current=list->Tail;
    return list->Current;

}

void * prevList(ListBomberos * list){
    if(!list->Current)return NULL;
    if(!list->Current->Prev)return NULL;
    list->Current=list->Current->Prev;
}

void pushFront(ListBomberos * list, Bombero * b) {

  if(!list->Head){
    list->Tail=b;
  }
  else{
    list->Head->Prev=b;
    b->Next=list->Head;
  }
  list->Head=b;
}

void pushCurrent(ListBomberos * list, Bombero * b){
  b->Next=list->Current->Next;
  //si agrega al final de la lista actualiza el tail
  if(!list->Current->Next)list->Tail=b;
  //De lo contrario lo agrega en la posicion cualquiera
  else list->Current->Next->Prev=b;

  b->Prev=list->Current;
  list->Current->Next=b;
 
}

void pushBack(ListBomberos * list, Bombero * b) {
    list->Current = list->Tail;
    pushCurrent(list,b);
}

void * popCurrent(ListBomberos * list) {
  Bombero* aux = malloc(sizeof(Bombero));
  aux = list->Current;

  //Si el nodo a eliminar se encuentra en la cabecera
  if(!list->Current->Prev){
    list->Head=list->Current->Next;
    list->Current->Next->Prev=NULL;
    list->Current=list->Current->Next;
    free(aux);
    return NULL;
  }
  //Si el nodo a eliminar se encuentra al final
  if(!list->Current->Next){
    list->Tail=list->Current->Prev;
    list->Current->Prev->Next=NULL;
    list->Current=list->Current->Prev;
    free(aux);
    return NULL;
  }
  //Si el nodo se encuentra en cualquier posicion
  list->Current->Prev->Next=list->Current->Next;
  list->Current->Next->Prev=list->Current->Prev;
  list->Current=list->Current->Next;
  free(aux);
}

void * popBack(ListBomberos * list) {
    list->Current = list->Tail;
    return popCurrent(list);
}

void * popFront(ListBomberos * list) {
    list->Current = list->Head;
    return popCurrent(list);
}

void cleanList(ListBomberos * list) {
    while (list->Head != NULL) {
        popFront(list);
    }
}

bool vacio(ListBomberos * list){
  if(!list->Head){
    return true;
  }
  return false;
}