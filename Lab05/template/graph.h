#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph GRAPH;  // não altere esta linha

GRAPH *graph_read();  // não altere esta linha

GRAPH *graph_create(int order);  // não altere esta linha
void graph_destroy(GRAPH *graph);  // não altere esta linha

bool graph_has_edge(const GRAPH *graph, int u, int v);  // não altere esta linha
int graph_edge_weight(const GRAPH *graph, int u, int v);  // não altere esta linha

void graph_print(const GRAPH *graph);  // não altere esta linha

void dijkstra(const GRAPH *graph, int u);  // não altere esta linha

// acrescente outras funções de desejar

#endif // GRAPH_H
