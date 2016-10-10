#include "item.h"

#ifndef LIST_H
#define LIST_H

/****************************************************************************************
*
*   1. Estruturas
*
*****************************************************************************************/

typedef struct elem {
	Item item;
 	struct elem *next;
} *net;

typedef struct list {
   net head;
} *list;

/****************************************************************************************
*
*   2. Prototipos
*
*****************************************************************************************/

/* Inicializa lista */
extern void LSinit();

/* Insere na lista */
extern void LSinsert(Item item);

/* Imprime m primeiros elementos do sistema */
extern void LSprint(int m);

/* Elimina lista */
extern void LSkill();

#endif