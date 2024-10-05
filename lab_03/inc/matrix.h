#pragma once

#include <stdio.h>

typedef struct
{
    size_t rows, columns;
    int **data;
} Matrix;

void print_matrix(Matrix *matrix);
