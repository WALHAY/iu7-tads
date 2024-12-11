#include "../inc/Graph.h"
#include <stdio.h>

Graph *createGraph(size_t size)
{
    Graph *graph = malloc(sizeof(Graph));
    if (graph)
    {
        graph->size = size;
        graph->buffer = calloc(size * size, sizeof(int));
        graph->matrix = malloc(size * sizeof(int *));
        for (size_t i = 0; i < size; ++i)
            graph->matrix[i] = graph->buffer + i * size;
    }
    return graph;
}

// Path *createPath(size_t size)
// {
//     Path *path = malloc(sizeof(Path));
//     if (path)
//     {
//         path->size = 0;
//         path->visited = malloc(size * sizeof(bool));
//         path->path = malloc(size * sizeof(int));
//     }
//     return path;
// }

Graph *importFromFile(FILE *file)
{
    if (!file)
        return NULL;

    size_t size = 0;
    if (1 != fscanf(file, "%zu\n", &size))
        return NULL;

    Graph *graph = createGraph(size);

    size_t from, to;
    while (fscanf(file, "%zu%zu", &from, &to) == 2)
        addEdge(graph, from, to);
    return graph;
}

void addEdge(Graph *graph, int from, int to)
{
    if (from >= graph->size || to >= graph->size)
        return;

    graph->matrix[from][to] = 1;
    graph->matrix[to][from] = 1;
}

void removeEdge(Graph *graph, int from, int to)
{
    if (from >= graph->size || to >= graph->size)
        return;

    graph->matrix[from][to] = 0;
    graph->matrix[to][from] = 0;
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
        Path currentPath = {0}; // createPath(graph->size);
        matrixDFS(graph, &currentPath, result, vertex);
    }
}
