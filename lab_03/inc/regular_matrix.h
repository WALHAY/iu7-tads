#pragma once

#include "sparse_matrix.h"
#include <stdlib.h>

typedef struct
{
    size_t rows;
    size_t columns;
    int *buffer;
    int **matrix;
} RegularMatrix;

RegularMatrix *create_regular_matrix(size_t rows, size_t columns);

RegularMatrix *from_sparse_to_regular_matrix(SparseMatrix *matrix);

SparseMatrix *from_regular_to_sparse_matrix(RegularMatrix *matrix);
