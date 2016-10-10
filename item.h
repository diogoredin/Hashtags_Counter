#ifndef ITEM_H
#define ITEM_H

/****************************************************************************************
*
*   1. Estruturas
*
*****************************************************************************************/

typedef struct hashtag {
    char *text;
	int count;
} *Item;

/****************************************************************************************
*
*   2. Prototipos
*
*****************************************************************************************/

/* Cria um novo Item */
extern Item NewItem(char*text, int size);

/* Elimino Item e liberto memoria associada */
extern void deleteItem(Item item);

/* Atualiza contador de um Item */
extern void updateCount(Item item);

/* Mostra o conteudo de um Item */
extern void showItem(Item x);

/* Devolve chave do item */
extern char* key(Item item);

/* Compara dois Items */
extern int cmpItem(const void *a, const void *b);

#endif