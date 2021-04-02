
#include <string.h>
#include <assert.h>
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

// Funciones del TDA a implementar

void * firstList(ListBomberos * list) {
    if(!list->Head)return NULL;
    list->Current=list->Head;
}
/*
void * nextList(ListBomberos * list) {
    if(!list->Current)return NULL;
    if(!list->Current->Next)return NULL;
    Bombero* Next = malloc(sizeof(Bombero));
    Next = list->Current->Next;
    list->Current=list->Current->Next;

}

void * lastList(ListBomberos * list) {
    if(!list->Tail)return NULL;
    list->Current=list->Tail;

}

void * prevList(ListBomberos * list){
    if(!list->Current)return NULL;
    if(!list->Current->Prev)return NULL;
    list->Current=list->Current->Prev;
    //return (void*)list->current->data;
}*/

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

/*
void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node* aux = malloc(sizeof(Node));
  aux = list->current;

  //Si el nodo a eliminar se encuentra en la cabecera
  if(!list->current->prev){
    list->head=list->current->next;
    list->current->next->prev=NULL;
    list->current=list->current->next;
    return (void*)aux->data;
  }
  //Si el nodo a eliminar se encuentra al final
  if(!list->current->next){
    list->tail=list->current->prev;
    list->current->prev->next=NULL;
    list->current=list->current->prev;
    return (void*)aux->data;
  }
  //Si el nodo se encuentra en cualquier posicion
  list->current->prev->next=list->current->next;
  list->current->next->prev=list->current->prev;
  list->current=list->current->next;
  return (void*)aux->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}*/