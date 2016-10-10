#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

/****************************************************************************************
*
*   INDEX - list.c
*
*   1. LSinit - Inicializa lista
*   2. LSinsert - Insere na lista
*   3. LSprint - Mostra Items da lista
*	  4. LSkill - Elimina lista
*
*****************************************************************************************/

static list list_init;

/* 1. Inicializa lista */
void LSinit() {

  /* Crio nova lista */
  list_init = malloc(sizeof(struct list));

  /* Primeiro elemento da lista a NULL */
  net head = NULL;

  /* Incializa propriedades da lista */
  list_init->head = head;

}

/* 2. Insere na lista */
void LSinsert(Item new_item) {

  /* Crio novo elemento na lista */
  net new = (net)malloc(sizeof(struct elem));

  /* Guardo ponteiro */
  new->item = new_item;

  /* Aponta para o proximo link (o que ja existia pq estamos a inserir no inicio) */
  new->next = list_init->head;

  /* Atualiza a cabeca */
  list_init->head = new;

}

/* 3. Mostra Items da lista */
void LSprint(int m) {

  /* Cria vetor adicional para ordenar os ponteiros */
  Item items[m];

  /* Variaveis temporarias */
  int i;
  net t;
  net cabeca;

  /* Cabeca da lista */
  cabeca = list_init->head;

  /* Coloca ponteiros em array */
  for( t = cabeca, i=0; t != NULL; t = t->next, i++ ) {
    items[i] = t->item;
  }

  /* Ordena os ponteiros com a funcao cmpItem */
  qsort(items, m, sizeof(Item), cmpItem);

  /* Imprime do fim para o inicio os items */
  for( i=m-1; i >= 0; i-- ) {
    showItem(items[i]);
  }

}

/* 4. Elimina lista */
void LSkill() {

  /* Variaveis temporarias */
  net t;
  net next_t;
  net cabeca;

  /* Cabeca da lista */
  cabeca = list_init->head;

  /* Percorre conexoes para as apagar */
  for( t = cabeca; t != NULL; ) {
    next_t = t->next;
    free(t);
    t = next_t;
  }

	/* Liberta memoria */
  free(list_init);

}