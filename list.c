
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
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

typedef struct Horario Horario;

struct Horario {
char dia[11];
char rut[5][12];
char name[5][30];
int disp[5];
int lugares;
};



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