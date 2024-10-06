#pragma once

#include "defines.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    size_t size;
    size_t rows, columns;
    size_t *columnIndex, *rowStartIndex;
    int *elements;
} SparseMatrix;

SparseMatrix *create_matrix(size_t rows, size_t columns, size_t elements);

int add_matrix_element(SparseMatrix *matrix, int element, size_t row, size_t column);

int generate_random_matrix(SparseMatrix *matrix, size_t elements);

int print_sparse_matrix(SparseMatrix *matrix);
