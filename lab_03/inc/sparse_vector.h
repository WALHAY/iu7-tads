#pragma once

#include "sparse_matrix.h"
#include <stdlib.h>

typedef struct
{
    size_t length;
    size_t size;
    int *elements;
    size_t *index;
} SparseVector;

SparseVector *create_vector(size_t length);

int add_vector_element(SparseVector *vector, int element, size_t index);

void generate_random_vector(SparseVector *vector, size_t elements);

int get_or_zero(SparseVector *vector, size_t index);

void print_sparse_vector(SparseVector *vector);
