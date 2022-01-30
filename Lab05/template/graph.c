#include "graph.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
};

struct graph {
  int order;
  //...
};

GRAPH *graph_read() {
}

GRAPH *graph_create(int order) {

}

void graph_destroy(GRAPH *graph) {

}

void graph_add_edge(GRAPH *graph, int u, int v, int w) {

}

bool graph_has_edge(const GRAPH *graph, int u, int v) {

}

int graph_edge_weight(const GRAPH *graph, int u, int v) {

}

void graph_print(const GRAPH *graph) {
  for (int u = 0; u < graph->order; ++u) {
    for (int v = 0; v < graph->order; ++v)
      if (graph_has_edge(graph, u, v))
        printf("%d ", graph_edge_weight(graph, u, v));
      else
        printf("∞ ");
    printf("\n");
  }
}

void dijkstra(const GRAPH *graph, int u) {
// encontra os arrays

//imprime resultado em stdout
}
