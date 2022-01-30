#include "graph.h"

int main() {
  // Parte 1: Ler o grafo
  GRAPH *graph = graph_read();
  //graph_print(graph); teste seu código antes de prosseguir

  // Parte 2: Dijkstra
  dijkstra(graph, 0);
  graph_destroy(graph);
}
