#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable.h"

/****************************************************************************************
*
*   INDEX - struct.c
*
*   1. Funcao de Codificacao
*
*   2. Funcoes Auxiliares
*     2.1. insertBeginList
*     2.2. searchList
*
*   2. Tabela Dispersao por Encadeamento Externo
*     2.1. STinit
*     2.2. STinsert
*     2.3. STsearch
*     2.4. STmax
*     2.5. STmax_update
*     2.6. STkill
*
*****************************************************************************************/

/****************************************************************************************
*
*   1. Funcao de Codificacao
*
*****************************************************************************************/

static int M;

/* 1.1. Funcao de codificacao */
int hash(char *v, int M) {

  /* Calcula media ponderada de uma chave com M primo */
  int h, a = 31415, b = 27183;
  for (h = 0; *v != '\0'; v++, a = a*b % (M-1)) {
    h = (a*h + *v) % M;
  }

  return h;

}

/****************************************************************************************
*
*   2. Funcoes Auxiliares
*
*****************************************************************************************/

/* 2.1. Insere elemento inicio da lista */
void insertBeginList(link *headptr, Item item_novo) {

  /* Cria novo link na lista */
  link new = (link)malloc(sizeof(struct node));

  /* Guarda o item novo link da lista */
  new->item = item_novo;

  /* Aponta para o proximo link (o que ja existia pq estamos a inserir no inicio) */
  new->next = *headptr;

  /* Atualiza a cabeca */
  *headptr = new;

}

/* 2.2. Procura elemento por chave */
Item searchList(link *headptr, Key v) {

  if( (*headptr) == NULL ) { return NULL; }

  /* Obtenho chave deste item */
  Item item = (*headptr)->item;

  /* Se for encontrei o meu item */
  if( strcmp(item->text, v) == 0 ) {
    return item;

  /* Verifico proximos links */
  } else {

    link proximo_link = (*headptr)->next;
    return searchList(&proximo_link, v);

  }

}

/****************************************************************************************
*
*   3. Tabela Dispersao por Encadeamento Externo
*
*****************************************************************************************/

static hashtable hashtable_init;
static link *heads;

/* 3.1. Inicializa hashtable */
void STinit(int max) {

  int i;

  /* Limite maximo da hashtable */
  M = max;

  /* Inicializa cabecas a NULL */
  heads = (link*)malloc(M*sizeof(link));

  for (i = 0; i < M; i++) {
    heads[i] = NULL;
  }

  /* Crio nova hastable */
  hashtable_init = malloc(sizeof(struct hashtable));

  /* Incializa propriedades da hashtable */
  hashtable_init->heads = heads;
  hashtable_init->M = M;
  hashtable_init->size = 0;
  hashtable_init->max = NULL;

}

/* 2.2. Insercao de elemento */
void STinsert(Item item) {
  int i = hash(key(item), M);
  insertBeginList(&heads[i], item);
}

/* 2.3. Procura de elemento */
Item STsearch(Key v) {
  int i = hash(v, M);
  return searchList(&heads[i], v);
}

/* 2.4. Retorna item maximo */
Item STmax() {
  Item item = hashtable_init->max;
  return STsearch( key(item) );
}

/* 2.5. Atualiza item maximo */
void STmax_update(Item item) {
  hashtable_init->max = item;
}

/* 2.6. Elimina hastable */
void STkill() {

  /* Liberta memoria das listas e hashtable */
  /* Os items sao anteriormente apagadas pela LSKill */
  int i;
  link t;
  link next_t;

  /* Percorre inicios das listas da hashtable */
  for (i = 0; i < M; i++) {

    /* Elimina elementos desta lista */
    for( t = heads[i]; t != NULL; ) {
      next_t = t->next;
      deleteItem(t->item);
      free(t);
      t = next_t;
    }

  }

  /* Liberta memoria da lista de listas e da Hashtable */
  free(hashtable_init->heads);
  free(hashtable_init);

}