#pragma once

#include "sparse_vector.h"
#include <stdlib.h>

typedef struct
{
    size_t length;
    int *data;
} RegularVector;

RegularVector *create_regular_vector(size_t length);

RegularVector *free_regular_vector(RegularVector *vector);

int generate_random_regular_vector(RegularVector *vector, float fill);

RegularVector *from_sparse_to_regular_vector(SparseVector *vector);

SparseVector *from_regular_to_sparse_vector(RegularVector *vector);
