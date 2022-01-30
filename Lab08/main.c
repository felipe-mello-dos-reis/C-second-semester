#include "graph.h"

int main(){
    GRAPH *graph = graph_read();
    articulation(graph);
    graph_destroy(graph);
    return 0;
}