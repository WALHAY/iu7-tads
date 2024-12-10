#include "../inc/Graph.h"
#include "../inc/GraphvizIntegration.h"
#include <stdio.h>

int main(void)
{
    size_t size = 8;
    Graph *graph = createGraph(size);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 2, 3);

    addEdge(graph, 4, 5);
    addEdge(graph, 5, 6);
    addEdge(graph, 5, 7);

    Path *result = createPath(size);
    findMaxSimplePath(graph, result);

    for (size_t i = 0; i < result->size; ++i)
        printf("%d\n", result->path[i]);

    drawGraphWithPath(graph, result, "Path");

    return 0;
}
