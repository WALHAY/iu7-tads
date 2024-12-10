#include "../inc/Graph.h"
#include <stdio.h>

void addEdge(Graph *graph, int from, int to)
{
    if (from >= graph->size || to >= graph->size)
        return;

    graph->matrix[from][to] = 1;
    graph->matrix[to][from] = 1;
}

void matrixDFS(Graph *graph, Path *currentPath, Path *maxPath, int vertex)
{
    currentPath->visited[vertex] = true;
    currentPath->path[currentPath->size++] = vertex;

    if (currentPath->size > maxPath->size)
        *maxPath = *currentPath;

    for (size_t nextVertex = 0; nextVertex < graph->size; nextVertex++)
        if (graph->matrix[vertex][nextVertex] == 1 && !currentPath->visited[nextVertex])
            matrixDFS(graph, currentPath, maxPath, nextVertex);

    currentPath->visited[vertex] = false;
    currentPath->size--;
}

void findMaxSimplePath(Graph *graph, Path *result)
{
    for (size_t vertex = 0; vertex < graph->size; ++vertex)
    {
        Path currentPath = {NULL};
        matrixDFS(graph, &currentPath, result, vertex);
    }
}
