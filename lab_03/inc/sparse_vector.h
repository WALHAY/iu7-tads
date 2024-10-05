#pragma once

#include "sparse_matrix.h"
#include <stdlib.h>

typedef struct
{
    size_t size;
    int *elements;
    size_t *index;
} SparseVector;

SparseVector *create_vector(size_t size);

void generate_random_vector(SparseVector *vector, size_t elements);

void print_sparse_vector(SparseVector *vector);
