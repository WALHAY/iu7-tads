#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    size_t size;
    int **matrix;
    int *buffer;
} Graph;

typedef struct
{
    size_t size;
    bool *visited;
    int *path;
} Path;

Graph *createGraph(size_t size);

Path *createPath(size_t size);

void addEdge(Graph *graph, int from, int to);

void matrixDFS(Graph *graph, Path *currentPath, Path *maxPath, int vertex);

void findMaxSimplePath(Graph *graph, Path *path);
