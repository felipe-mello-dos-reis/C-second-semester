#include "graph.h"

int main() {
  //Part 1: read graph
  GRAPH *graph = graph_read();
  
  //graph_print(graph);  //teste seu código antes de prosseguir

  // Parte 2: Dijkstra
  dijkstra(graph, 0);
  graph_destroy(graph);
}
