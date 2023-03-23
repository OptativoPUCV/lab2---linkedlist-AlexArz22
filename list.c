#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *list=malloc(sizeof(List));
  if(list==NULL) return(NULL);
  list->head=NULL;
  list->tail=NULL;
  return list;
}

void * firstList(List * list) {
  if(list==NULL || list->head==NULL) return NULL;
  list->current=list->head;
  return list->current->data;
}

void * nextList(List * list) {
  if(list==NULL || list->current==NULL || list->current->next==NULL) return NULL;
  list->current=list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(list==NULL || list->tail==NULL) return NULL;
  list->current=list->tail;
  return list->current->data;
}

void * prevList(List * list) {
  if(list==NULL || list->current==NULL || list->current->prev==NULL) return NULL;
  list->current=list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  if(list==NULL) return;
  Node *nodo=createNode(data);
  if(list->head==NULL)
  {
    list->head=nodo;
    list->current=nodo;
    if(list->tail==NULL) list->tail=nodo;
  }
  else{
    list->head->prev=nodo;
    nodo->next=list->head;
    list->head=nodo;
  }
  return;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if(list==NULL || list->current==NULL) return;
  Node *nodo=createNode(data);
  
  if(list->current==list->tail)
  {
    list->current->next=nodo;
    list->tail=nodo;
    list->tail->prev=list->current;
    list->current=list->tail;
    return;
  }
  else{

    Node *nodoSiguiente=list->current->next;
    list->current->next=nodo;
    nodo->prev=list->current;
    list->current=list->current->next;
    list->current->next=nodoSiguiente;
    nodoSiguiente->prev=list->current;
    
  }
  list->current=nodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}
/*6. Programe la función `void* popCurrent(List * list)`, la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el **dato** del nodo eliminado.
> **Nota**: El current debe quedar apuntando al nodo siguiente del eliminado.*/
void * popCurrent(List * list) {
  if(list->current==NULL) return NULL;
  int *dato= list->current->data;
  if(list->current==list->head)
  {
    list->head=list->current->next;
    list->head->prev=NULL;
    free(list->current);
  }
  else
  {
    if(list->current==list->tail)
    {
      list->tail=list->current->prev;
      list->tail->next=NULL;
      free(list->current);
    }
    else
    {
      Node *siguiente=list->current->next;
      Node *anterior=list->current->prev;
      anterior->next=siguiente;
      siguiente->prev=anterior;
      free(list->current);
    }
  }
  return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}