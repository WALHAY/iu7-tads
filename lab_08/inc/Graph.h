#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    size_t size;
    int **matrix;
    int *buffer;
} Graph;

typedef struct
{
    bool visited[1000];
    int path[1000];
    size_t size;
} Path;

Graph *createGraph(size_t size);

// Path *createPath(size_t size);

Graph *importFromFile(FILE *file);

void addEdge(Graph *graph, int from, int to);

void removeEdge(Graph *graph, int from, int to);

void matrixDFS(Graph *graph, Path *currentPath, Path *maxPath, int vertex);

void findMaxSimplePath(Graph *graph, Path *path);
