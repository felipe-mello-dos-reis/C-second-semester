#include "digraph.h"
#include "stack.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INF 9999

struct edge
{
	int index;
	EDGE *next;
};

struct digraph
{
	int order;
	EDGE **edges;
};

DIGRAPH *digraph_read()
{
	// Part 0: create digraph
	int order, u, v;
	assert(scanf("%d", &order) == 1);
	DIGRAPH *digraph = digraph_create(order);
	while (scanf("%d %d", &u, &v) != EOF)
	{
		digraph_add_edge(digraph, u, v);
	}
	return digraph;
}

DIGRAPH *digraph_create(int order)
{
	DIGRAPH *digraph = (DIGRAPH *)malloc(sizeof(DIGRAPH));
	assert(digraph != NULL);
	digraph->order = order;
	digraph->edges = (EDGE **)malloc(sizeof(EDGE *) * order);
	assert(digraph->edges != NULL);
	//Creating all edges as NULL
	for (int i = 0; i < order; i++)
	{
		digraph->edges[i] = NULL;
	}
	return digraph;
}

void digraph_destroy(DIGRAPH *digraph)
{
	for (int i = 0; i < digraph->order; i++)
	{
		EDGE *aux;
		while (digraph->edges[i] != NULL)
		{
			aux = digraph->edges[i];
			digraph->edges[i] = digraph->edges[i]->next;
			free(aux);
			aux = NULL;
		}
	}
	free(digraph);
	digraph = NULL;
}

static EDGE *digraph_create_edge(int v){
	EDGE *aux = (EDGE *)malloc(sizeof(EDGE));
	aux->index = v;
	aux->next = NULL;
	return aux;
}
/*
void digraph_add_edge(DIGRAPH *digraph, int u, int v)
{
	EDGE *aux = digraph_create_edge(v);
	aux->next = digraph->edges[u];
	digraph->edges[u] = aux;
}
*/

void digraph_add_edge(DIGRAPH *digraph, int u, int v)
{
    if(digraph->edges[u] == NULL)
        digraph->edges[u] = digraph_create_edge(v);

    else{
	    EDGE *aux = digraph->edges[u];
        while(aux->next != NULL)
            aux = aux->next;
        aux->next = digraph_create_edge(v);
    }
}


bool digraph_has_edge(const DIGRAPH *digraph, int u, int v) {
	EDGE *aux = digraph->edges[u];
	while(aux != NULL) {
		if(aux->index == v)
			return true;
		aux = aux->next;
	}
	return false;
}

typedef enum { WHITE, GRAY, BLACK } COLOR; 

void top_sort(const DIGRAPH *digraph, STACK *stack, COLOR *color, int i){
     if(!stack_isEmpty(stack))
        if(stack_top(stack) == INF){     // If not DAG
            return;
        }
    color[i] = GRAY;
    for(EDGE *aux = digraph->edges[i]; aux != NULL; aux = aux->next){
        if(color[aux->index] == WHITE)
            top_sort(digraph, stack, color, aux->index);
        if(color[aux->index] == GRAY){  // If not DAG
            stack_push(stack, INF);
            return;
        }
    }
    color[i] = BLACK;
    stack_push(stack, i);
}

void topological_sort(const DIGRAPH *digraph){

    STACK *stack = stack_create();  
    COLOR *color = (COLOR *)malloc(sizeof(COLOR)*digraph->order);
    for(int i = 0; i < digraph->order; i++){
        color[i] = WHITE;
    }

    for(int i = 0; i < digraph->order; i++){
        if(color[i] == WHITE){
            top_sort(digraph, stack, color, i);
        }
    }
    if(stack_top(stack) == INF){    // If not DAG
        printf("\n");
        return;
    }
    else{
        while(!stack_isEmpty(stack)){
            printf("%d ", stack_top(stack));
            stack_pop(stack);
        }
    }
    stack_destroy(stack);
    free(color);
}

/*
3406
3407
3428
3532
3539
3544
3555
*/