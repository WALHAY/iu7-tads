#include "../inc/Graph.h"
#include <stdio.h>

int main(void)
{
    size_t size = 8;
    Graph *graph = createGraph(size);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 2, 3);
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
            printf("%d ", graph->matrix[i][j]);
        printf("\n");
    }
    Path result;
    findMaxSimplePath(graph, &result);

    for (size_t i = 0; i < result.size; ++i)
        printf("%d\n", result.path[i]);

    return 0;
}
