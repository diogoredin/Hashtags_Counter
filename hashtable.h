#include "item.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

/****************************************************************************************
*
*   1. Estruturas
*
*****************************************************************************************/

typedef struct node {
   Item item;
   struct node *next;
} *link;

typedef struct hashtable {
   link* heads;
   Item max;
   int M, size;
} *hashtable;

typedef char* Key;

/****************************************************************************************
*
*   2. Prototipos
*
*****************************************************************************************/

/* Inicializa tabela de dispersao */
extern void STinit(int max);

/* Insercao novo elemento */
extern void STinsert(Item item);

/* Procura de elemento */
extern Item STsearch(Key v);

/* Retorna elemento maximo */
extern Item STmax();

/* Atualiza elemento maximo */
extern void STmax_update(Item item);

/* Elimina hastable */
extern void STkill();

#endif