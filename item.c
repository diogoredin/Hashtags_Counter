#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "item.h"

/****************************************************************************************
*
*   INDEX - item.c
*
*   1. NewItem - Cria novo Item
*   2. updateCount - Atualiza Item
*	3. deleteItem - Elimina Item
*	4. showItem - Mostra Item
*	5. cmpItem - Compara Items
*
*****************************************************************************************/

/* 1. Cria um novo Item */
Item NewItem(char *text, int size) {

	/* Cria novo item com tamanho suficiente */
	Item newItem = (Item) malloc(sizeof(struct hashtag));

	/* Reservo espaco para o nome e guardo */
	newItem->text = (char*) malloc(sizeof(char)*size); 
	strcpy(newItem->text, text);

	/* Inicializo contador */
	newItem->count = 1;

	/* Devolve ponteiro para novo item */
	return newItem;
}

/* 2. Atualizo Item */
void updateCount(Item item) {

	/* Incrementa contador */
    item->count++;

}

/* 3. Elimino Item */
void deleteItem(Item item) {

	/* Liberto memoria associada */
    free(item->text);
    free(item);

}

/* 4. Mostra o conteudo de um Item */
void showItem(Item x) {

	/* Imprime para stdout hashtag e o seu contador */
	printf("%s %d\n", x->text, x->count);

}

/* 5. Devolve chave do item */
char* key(Item item) {
	return item->text;
}

/* 6. Compara dois Items  */
int cmpItem(const void *a, const void *b) {

	/* Converte ponteiros para o vetor para ponteiros para items */
	const Item *p_a = a;
	const Item *p_b = b;
	const Item item_a = *p_a;
	const Item item_b = *p_b;

	/* Devolve 1 ou -1 se nao sao iguais pelo contador */
	if (item_a->count > item_b->count) return 1;
	if (item_a->count < item_b->count) return -1;

	/* Devolve 1 ou -1 se nao sao iguais lexicograficamente */
	if ( strcmp ( item_a->text, item_b->text ) < 0 ) return 1;
	if ( strcmp ( item_a->text, item_b->text ) > 0 ) return -1;

	/* Devolve 0 se sao estritamente iguais */
	return 0;

}