/* Faça aqui sua implementação. */
#include <stdio.h>
#include <stdlib.h>

#include "deque.h"
typedef struct noh NOH;
struct noh
{
	int elem;
	NOH *prox;// = (NOH *)malloc(sizeof(NOH));
	NOH *prev;// = (NOH *)malloc(sizeof(NOH));
};
struct deque
{
	int size;
	NOH *top, *bot;
};


/*
 * Retorna um deque recém-alocada.
 */
DEQUE *deque_create(void)
{
	DEQUE *deque = (DEQUE *)malloc(sizeof(DEQUE));
	//deque->top = (NOH *)malloc(sizeof(NOH));
	//deque->bot = deque->top;
	deque->size = 0;
	deque->top = NULL;
	deque->bot = NULL;
	return deque; 
}

/*
 * Destrói um deque previamente criado, liberando toda sua memória.
 */
void deque_destroy(DEQUE *deque)
{
	deque_empty(deque);
	free(deque->top);
	free(deque);
}
/*
 * Limpa o deque, removendo todos os elementos.
 */
void deque_empty(DEQUE *deque)
{
	while(deque->size > 0)
		deque_removeFirst(deque);
}
/*
 * Imprime todos os elementos dp deque na mesma linha separados por espaço.
 * Ao final do deque, um '\n' é escrito.
 */
void deque_print(const DEQUE *deque)
{
	if(deque->size == 0)
	{
		printf("\n");
		return;
	}
	NOH *aux;
	aux = deque->top;
	for(int i = 0; i < deque->size - 1; i++)
	{
		printf("%d ", aux->elem);
		aux = aux->prev;
	}
	printf("%d\n", aux->elem);
}
/*
 * Retorna o primeiro elemento do deque.
 */
int deque_first(const DEQUE *deque)
{
	return deque->top->elem;
}
/*
 * Retorna o último elemento do deque.
 */
int deque_last(const DEQUE *deque)
{
	return deque->bot->elem;
}

/*
 * Insere um novo elemento `element` no início do deque.
 */
void deque_insertFirst(DEQUE *deque, int element)
{
	if(deque->size == 0)
	{
		deque->top = (NOH *)malloc(sizeof(NOH));
		deque->bot = deque->top;
		deque->size++;
		deque->top->elem = element;
		deque->top->prox = NULL;
		deque->top->prox = NULL;
		return;
	}
	deque->size++;
	deque->top->prox = (NOH *)malloc(sizeof(NOH));
	deque->top->prox->prev = deque->top;
	deque->top = deque->top->prox;
	deque->top->elem = element;
	deque->top->prox = NULL;
}
/*
 * Insere um novo elemento `element` no fim do deque.
 */
void deque_insertLast(DEQUE *deque, int element)
{
	if(deque->size == 0)
	{
		deque->bot = (NOH *)malloc(sizeof(NOH));
		deque->top = deque->bot;
		deque->size++;
		deque->bot->elem = element;
		deque->bot->prox = NULL;
		deque->bot->prox = NULL;
		return;
	}
	deque->size++;
	deque->bot->prev = (NOH *)malloc(sizeof(NOH));
	deque->bot->prev->prox = deque->bot;
	deque->bot = deque->bot->prev;
	deque->bot->elem = element;
	deque->bot->prev = NULL;
}

/*
 * Remove o primeiro elemento do deque.
 */
void deque_removeFirst(DEQUE *deque)
{
	if(deque->size == 0)
		return;
	if(deque->size == 1)
	{
		free(deque->top);
		deque->size--;
		deque->top = NULL;
		deque->bot = NULL;
		return;
	}
	deque->size--;
	deque->top->prev->prox = NULL;
	NOH *aux = deque->top->prev;
	free(deque->top);
	deque->top = aux;
}

/*
 * Remove o último elemento do deque.
 */
void deque_removeLast(DEQUE *deque)
{
	if(deque->size == 0)
		return;
	if(deque->size == 1)
	{
		free(deque->top);
		deque->size--;
		deque->top = NULL;
		deque->bot = NULL;
		return;
	}
	deque->size--;
	deque->bot->prox->prev = NULL;
	NOH *aux = deque->bot->prox;
	free(deque->bot);
	deque->bot = aux;
}
/*
 * Retorna o número de elementos do deque.
 */
int deque_size(const DEQUE *deque)
{
	return deque->size;
}
