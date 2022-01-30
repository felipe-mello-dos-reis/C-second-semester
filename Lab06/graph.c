#include "graph.h"
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
	int weight;
	EDGE *next;
};

struct graph
{
	int order;
	EDGE **edges;
};

GRAPH *graph_read()
{
	// Part 0: create graph
	int order, u, v, w;
	assert(scanf("%d", &order) == 1);
	GRAPH *graph = graph_create(order);
	while (scanf("%d %d %d", &u, &v, &w) != EOF)
	{
		graph_add_edge(graph, u, v, w);
	}
	return graph;
}

GRAPH *graph_create(int order)
{
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

void graph_destroy(GRAPH *graph)
{
	for (int i = 0; i < graph->order; i++)
	{
		EDGE *aux;
		while (graph->edges[i] != NULL)
		{
			aux = graph->edges[i];
			graph->edges[i] = graph->edges[i]->next;
			free(aux);
			aux = NULL;
		}
	}
	free(graph);
	graph = NULL;
}

static EDGE *graph_create_edge(int v, int w){
	EDGE *aux = (EDGE *)malloc(sizeof(EDGE));
	aux->index = v;
	aux->weight = w;
	aux->next = NULL;
	return aux;
}

void graph_add_edge(GRAPH *graph, int u, int v, int w)
{
	EDGE *aux = graph_create_edge(v, w);
	aux->next = graph->edges[u];
	graph->edges[u] = aux;
	EDGE *aux_2 = graph_create_edge(u, w);
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

int graph_edge_w(const GRAPH *graph, int u, int v) {
	if(!graph_has_edge(graph, u, v))
		return -INF;

	EDGE *aux = graph->edges[u];
	while(aux != NULL){
		if(aux->index == v)
			return aux->weight;
		aux = aux->next;
	}
	return -INF;
}

void graph_print(const GRAPH *graph) {
  for (int u = 0; u < graph->order; ++u) {
    for (int v = 0; v < graph->order; ++v)
      if (graph_has_edge(graph, u, v))
        printf("%d ", graph_edge_w(graph, u, v));
      else
        printf("∞ ");
    printf("\n");
  }
}


int find_minimum(bool *visited,  int order, int *distance){
	int i, ind;
	int min = INF;
	for(i = 0; i < order; i++)
		if(distance[i] <= min && visited[i] == false){
			min = distance[i];
			ind = i;
		}
	return ind;
}
/*
//function to find the weight between u and v
int weight(EDGE *vertex, int u, int v){
	if(u == v)
		return 0;
	while(vertex->index != v && vertex->next != NULL)
		vertex = vertex->next;
	if(vertex->index == v)
		return vertex->weight;
	else
		return INF;
}
*/
void dijkstra(const GRAPH *graph, int origin){
	// create array of nodes not visited
	bool *visited = (bool *)malloc(sizeof(bool)*graph->order);
	for(int i = 0; i < graph->order; i++)
		visited[i] = false;

	// create array of distance
	int *distance = (int *)malloc(sizeof(int)*graph->order); 
	distance[0] = 0;
	for(int i = 1; i < graph->order; i++)
		distance[i] = INF;
		
	//creat array of previous node
	int *father = (int *)malloc(sizeof(int)*graph->order); 
	for(int i = 0; i < graph->order; i++)
		father[i] = -1;
	
	int v = origin;
	for(int i = 0; i < graph->order; i++){
		v = find_minimum(visited, graph->order, distance);
		for(EDGE *aux = graph->edges[v]; aux != NULL; aux = aux->next){
			int u = aux->index;
			if(distance[u] > distance[v] + graph_edge_w(graph, u, v)){
				distance[u] = distance[v] + graph_edge_w(graph, u, v);
				father[u] = v;
			}
			visited[v] = true;
		}
	}
	


	//function to print the distances
	STACK *stack = stack_create();
	for(int i = 1; i < graph->order; i++){
		v = i;
		if(distance[i] != INF){
			while(father[v] != -1){
				stack_push(stack, v);
				v = father[v];
			}
			printf("0 ");
			while(!stack_isEmpty(stack)){
				printf("%d ", stack_top(stack));
				stack_pop(stack);
			}
			printf(": %d\n", distance[i]);
		}
	}

	//Liberation of memory
	stack_destroy(stack);
	free(visited);
	free(father);
	free(distance);
}
/*
while(!stack_isEmpty(stack)){

	int v = stack_top(stack);
	//para todos vizinhos de V
	if(distance[u] > distance[v] + weight(u,v))
		distance[u] = distance[v] + weight(u,v);
	stack_pop(stack);
	visited[v] = true;]
	stack_push(find_minimum(distance))
}
*/
// //imprime resultado em stdout
// }

