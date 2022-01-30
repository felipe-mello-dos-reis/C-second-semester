/* Faça aqui sua solução conforme visto em aula. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
struct stack
{
	int elem;
	STACK *prox;
};

STACK *stack_create(void)
{
	STACK *stack = NULL;
	return stack;
}
void stack_destroy(STACK *stack)
{
	while(stack_isEmpty(stack) == 0)
		stack_pop(stack);
	free(stack);
}

bool stack_isEmpty(const STACK *stack)
{
	if(stack == NULL)
		return 1;
	else
		return 0;
}
int stack_top(const STACK *stack)
{
	assert(stack_isEmpty(stack) == 0);
	return stack->prox->elem;
}
void stack_push(STACK *stack, int element)
{
	STACK *aux = (STACK *)malloc(sizeof(STACK));
	aux->elem = element;
	aux->prox = stack;
	stack = aux;

}
void stack_pop(STACK *stack)
{
	assert(stack_isEmpty(stack) == 0);
	STACK *aux = stack->prox;
	stack->prox = stack->prox->prox;
	free(aux);
}
