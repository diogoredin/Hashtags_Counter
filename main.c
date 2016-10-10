#include "headers.h"

/**********************************   Diogo Redin 84711   *******************************
*
*
*   PROGRAMA CONTAGEM HASHTAGS - PROJETO II IAED
*   http://fenix.tecnico.ulisboa.pt/downloadFile/1970943312278220/iaed_2016_16-2s-p2.pdf
*
*
*****************************************************************************************/

/****************************************************************************************
*
*	INDEX
*
*	MAIN.C
*
*	1. Ciclo Principal
*	2. Funcoes Auxiliares
*		2.1. Split
*		2.2. hashtag_nova
*		2.3. hashtag_existente
*	3. Comandos
*		3.1.  A: Processa uma mensagem incrementando para cada # o contador respectivo;
*		3.2.  S: Mostra o nr de #s distintas e o nr total ocorrencias de todas as #s;
*		3.3.  M: Mostra a # mais popular;
*		3.4.  L: Lista todas as #s ordenadamente;
*
*   HASHTABLE.C
*
*   1. Funcao de Codificacao
*   2. Funcoes Auxiliares
*     2.1. insertBeginList
*     2.2. removeItemList
*     2.3. searchList
*   3. Tabela Dispersao por Encadeamento Externo
*     3.1. STinit
*     3.2. STinsert
*     3.3. STsearch
*     3.4. STmax
*     3.5. STmax_update
*     3.6. STkill
*
*	LIST.C
*
*   1. LSinit - Inicializa lista
*   2. LSinsert - Insere na lista
*	3. LSkill - Elimina lista
*	4. LSprint - Mostra Items da lista
*
*	ITEM.C
*
*   1. NewItem - Cria novo Item
*   2. updateCount - Atualiza Item
*	3. deleteItem - Elimina Item
*	4. showItem - Mostra Item
*	5. cmpItem - Compara Items
*
****************************************************************************************/

int nr_hastags_diferentes = 0;
int nr_hastags_total = 0;

/****************************************************************************************
*
*   1. CICLO PRINCIPAL
*
*****************************************************************************************/

int main() {

	/* Inicializacao Hastable & Lista Auxiliar */
	/* 10007 e um numero primo grande utilizado na funcao de hashing */
	STinit(10007);
	LSinit();

	while(1) {
        int executa = getchar();
	if ( executa == 'a') comando_A();
        else if ( executa == 's' ) { comando_S(); getchar(); }
        else if ( executa == 'm' ) { comando_M(); getchar(); }
        else if ( executa == 'l' ) { comando_L(); getchar(); }
        else if ( executa == 'x' ) { STkill(); LSkill(); return EXIT_SUCCESS; } 
        else { printf("Comando desconhecido.\n"); STkill(); LSkill(); return EXIT_FAILURE; }
	}

}

/****************************************************************************************
*
*   2.1. FUNCOES AUXILIARES
*	Split: Separa o input em tokens e processa-os
*
*****************************************************************************************/

/* Lista de caracteres que separam tokens */
static const char separators[] = {' ','\t',',',';','.','?','!','"','\n',':','\0'};

/* Divide input em tokens e encontra hashtags */
void split(char *input) {

	/* Obtem primeiro token */
    char *token = strtok(input, separators);

    /* Tamanho da hashtag */
    int size;

    /* Enquanto existem tokens */
    while ( token!=NULL ) {

    	/* Se o token e uma hashtag processa-a */
        if ( token[0] == '#' ) {

        	/* Atualiza hashtag se ja existe */
        	if ( STsearch(token) != NULL ) {
        		hashtag_existente(token);

			/* Cria nova hashtag */
        	} else {

        		/* Conta tamanho hashtag */
        		size = strlen(token) + 1;
        		hashtag_nova(token, size);

        	}

        }

        /* Obtem proximo token */
        token = strtok(NULL, separators);

    }

}

/****************************************************************************************
*
*   2.2. FUNCOES AUXILIARES
*	hashtag_nova: Adiciona hashtag nova ao sistema
*
*****************************************************************************************/

void hashtag_nova( char* token, int size ) {

	/* Cria nova hashtag */
	Item hashtag;
	hashtag = NewItem(token, size);

	/* Se e a primeira hastag consideramos como mais popular */
	if( nr_hastags_total == 0 ) { 
		STmax_update( hashtag );
	}

	/* Insere hashtag */
	STinsert(hashtag);
	LSinsert(hashtag);

	/* Incrementa numero hashtags diferentes */
	nr_hastags_diferentes++;

	/* Incrementa numero hashtags total */
	nr_hastags_total++;

	/* Obtem hastag mais popular */
	Item hashtag_popular;
	hashtag_popular = STmax();

	/* Se a nova hashtag for mais popular atualiza */
	if ( cmpItem(&hashtag, &hashtag_popular) > 0 ) {
		STmax_update( hashtag );
	}

}

/****************************************************************************************
*
*   2.3. FUNCOES AUXILIARES
*	hashtag_existente: Atualiza sistema com nova ocorrencia da hashtag
*
*****************************************************************************************/

void hashtag_existente( char* token ) {

	/* Encontra hashtag */
	Item hashtag;
	hashtag = STsearch(token);

	/* Atualiza contador hashtag */
	updateCount(hashtag);

	/* Incrementa numero hashtags total */
	nr_hastags_total++;

	/* Obtem hastag mais popular */
	Item hashtag_popular;
	hashtag_popular = STmax();

	/* Se a nova hashtag for mais popular atualiza */
	if ( cmpItem(&hashtag, &hashtag_popular) > 0 ) {
		STmax_update( hashtag );
	}

}

/****************************************************************************************
*
*   3.1. COMANDOS
*	A: Processa uma mensagem incrementando para cada # o contador respectivo
*
*****************************************************************************************/

void comando_A() {

	/* Contadores e vetor de caracteres */
	int c, i = 0;
	char s[DIM_LINHA];

	/* Por cada caracter introduzido guarda no vetor */
	while ( i<DIM_LINHA-1 && (c = getchar()) != EOF && c != '\n' ) {
		if ( c >= 'A' && c <= 'Z' ) { c = tolower(c); }
		s[i++] = c;
	}

	/* Termina linha */
	s[i] = '\0';

	/* Divide linha em tokens e conta hashtags */
	split(s);

}

/****************************************************************************************
*
*   3.2. COMANDOS
*	S: Mostra o nr de #s distintas e o nr total ocorrencias de todas as #s
*
*****************************************************************************************/

void comando_S() {

	/* Imprime distintas e total */
	printf("%d %d\n", nr_hastags_diferentes, nr_hastags_total);

}

/****************************************************************************************
*
*   3.3. COMANDOS
*	M: Mostra a # mais popular
*
*****************************************************************************************/

void comando_M() {

	/* Se houver hashtags */
	if ( nr_hastags_total > 0 ) {

		/* Obtem hastag mais popular */
		Item popular;
		popular = STmax();

		/* Imprime a hashtag mais popular */
		showItem(popular);

	}

}

/****************************************************************************************
*
*   3.4. COMANDOS
*	L: Lista todas as #s ordenadamente
*
*****************************************************************************************/

void comando_L() {

	/* Se houver hashtags */
	if ( nr_hastags_total > 0 ) {

		/* Nr hashtags a imprimir */
		int m;
		m = nr_hastags_diferentes;

		/* Imprime as m hashtags guardadas na lista auxiliar */
		LSprint(m);

	}	

}