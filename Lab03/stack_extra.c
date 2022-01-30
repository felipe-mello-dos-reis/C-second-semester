/* Faça aqui sua solução. */
#include <stdio.h>
#include "stack_extra.h"
#include <stdlib.h>
#include <assert.h>
/*
 * Imprime os valores da pilha do fundo para o cima separados por espaço.
 * No fim da impressão um '\n' é escrito.
 */

void stack_printBottomUp(STACK *stack)

{
	if(stack_isEmpty(stack) == 1)
	{
		printf("\n");
		return;
	}
	STACK *aux = stack_reverse(stack);
	while(stack_isEmpty(aux) == 0)
	{
		printf("%d ", stack_top(aux));
		stack_pop(aux);
	}
	printf("\n");
	stack_destroy(aux);
}

/*
 * Imprime os valores da pilha do topo para o baixo separados por espaço.
 * No fim da impressão um '\n' é escrito.
 */
void stack_printTopDown(STACK *stack)
{
	if(stack_isEmpty(stack) == 1)
	{
		printf("\n");
		return;
	}
	STACK *aux1 = stack_reverse(stack);
	STACK *aux2 = stack_reverse(aux1);
	while(stack_isEmpty(aux2) == 0)
	{
		printf("%d ", stack_top(aux2));
		stack_pop(aux2);
	}
	printf("\n");
	stack_destroy(aux1);
	stack_destroy(aux2);
}
/*
 * Retorna uma nova pilha com os valores invertidos, porém mantendo a pilha de
 * entrada inalterada.
 */
STACK *stack_reverse(STACK *stack)
{
	assert(stack_isEmpty(stack) == 0); //conferir para caso stack_isEmpty
	STACK *new_stack1 = stack_create();
	STACK *new_stack2 = stack_create();
	while(stack_isEmpty(stack) == 0)
	{
		stack_push(new_stack1, stack_top(stack));
		stack_push(new_stack2, stack_top(stack));
		stack_pop(stack);
	}
	while(stack_isEmpty(new_stack2) == 0)
	{
		stack_push(stack, stack_top(new_stack2));
		stack_pop(new_stack2);
	}
	stack_destroy(new_stack2);
	return new_stack1;
}
/*
 * Pilha a pilha `b` sobre a pilha `a`, deixando a pilha `b` vazia.
 */
void stack_stack(STACK *a, STACK *b)
{
	STACK *aux = stack_reverse(b);
	while(stack_isEmpty(aux) == 0)
	{
		stack_push(a,stack_top(aux));
		stack_pop(aux);
	}
	while(stack_isEmpty(b) == 0)
	{
		stack_pop(b);
	}
}
