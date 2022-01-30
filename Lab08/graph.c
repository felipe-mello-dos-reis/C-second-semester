#include "graph.h"
#include "stack.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INF 9999

struct edge{
	int index;
	EDGE *next;
};

struct graph{
	int order;
	EDGE **edges;
};

typedef enum { WHITE, GRAY, BLACK } COLOR; 

GRAPH *graph_read(){
	// Part 0: create graph
	int order, u, v;
	assert(scanf("%d", &order) == 1);
	GRAPH *graph = graph_create(order);
	while (scanf("%d %d", &u, &v) != EOF)
	{
		graph_add_edge(graph, u, v);
	}
	return graph;
}

GRAPH *graph_create(int order){
	GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
	assert(graph != NULL);
	graph->order = order;
	graph->edges = (EDGE **)malloc(sizeof(EDGE *) * order);
	assert(graph->edges != NULL);
	//Creating all edges as NULL
	for (int i = 0; i < order; i++)
	{
		graph->edges[i] = NULL;
	}
	return graph;
}

void graph_destroy(GRAPH *graph){
	for (int i = 0; i < graph->order; i++)
	{
		EDGE *aux;
		while (graph->edges[i] != NULL)
		{
			aux = graph->edges[i];
			graph->edges[i] = graph->edges[i]->next;
			free(aux);
		}
	}
	free(graph->edges);
	graph->edges = NULL;
	free(graph);
}

static EDGE *graph_create_edge(int v){
	EDGE *aux = (EDGE *)malloc(sizeof(EDGE));
	aux->index = v;
	aux->next = NULL;
	return aux;
}

void graph_add_edge(GRAPH *graph, int u, int v){
	EDGE *aux = graph_create_edge(v);
	aux->next = graph->edges[u];
	graph->edges[u] = aux;
	EDGE *aux_2 = graph_create_edge(u);
	aux_2->next = graph->edges[v];
	graph->edges[v] = aux_2;
}

bool graph_has_edge(const GRAPH *graph, int u, int v) {
	EDGE *aux = graph->edges[u];
	while(aux != NULL) {
		if(aux->index == v)
			return true;
		aux = aux->next;
	}
	return false;
}

int min(int x, int y){
	if(x > y)
		return y;
	else
		return x;
}

void find_artic(GRAPH *graph, int u, int *m, int *p, int *e, bool *logic, int dfsRoot, int *rootChildren){
	m[u] = e[graph->order];
	e[u] = e[graph->order];
	e[graph->order]++;
	for(EDGE *aux = graph->edges[u]; aux != NULL; aux = aux->next){
		int v = aux->index;
		if(e[v] == INF){
			p[v] = u;
			if(u == dfsRoot){
				*rootChildren = *rootChildren + 1;
			}
			find_artic(graph, v, m, p, e, logic, dfsRoot, rootChildren);
			if(m[v] >= e[u])
				logic[u] = true;
			m[u] = min(m[u], m[v]);
		}
		else if(v != p[u]){
			m[u] = min(m[u], e[v]);
		}
	}
}

void articulation(GRAPH *graph){
	int *p = (int *)malloc(sizeof(int)*graph->order); // antecessor
	int *e = (int *)malloc(sizeof(int)*(graph->order + 1)); // tempo de descoberta, a ultima posição guarda o relogio de Tarjan
	int *m = (int *)malloc(sizeof(int)*graph->order); // ancestral mais distante acessível diretamente
   	bool *logic = (bool *)calloc(graph->order, sizeof(bool));

	for(int u = 0; u < graph->order; u++){
		e[u] = INF;
		p[u] = m[u] = logic[u] = 0;
    }
	e[graph->order] = 0; // t <- 0

	int dfsRoot, rootChildren;
	for(int u = 0; u < graph->order; u++){
		if(e[u] == INF){
			dfsRoot = u;
			rootChildren = 0;
			find_artic(graph, u, m, p, e, logic, dfsRoot, &rootChildren);
			logic[u] = (rootChildren > 1);
		}
	}

	for(int u = 0; u < graph->order; u++){
		if(logic[u])
			printf("%d\n", u);
	}

	free(p);
	free(e);
	free(m);
	free(logic);
}