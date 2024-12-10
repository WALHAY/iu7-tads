#pragma once

#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct
{
    int **matrix;
    int *buffer;
    size_t size;
} Graph;

typedef struct
{
    bool visited[MAX_SIZE];
    int path[MAX_SIZE];
    size_t size;
} Path;

Graph *createGraph(size_t size);

void addEdge(Graph *graph, int from, int to);

void matrixDFS(Graph *graph, Path *currentPath, Path *maxPath, int vertex);

void findMaxSimplePath(Graph *graph, Path *path);
