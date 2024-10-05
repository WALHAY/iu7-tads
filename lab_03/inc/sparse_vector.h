#pragma once

#include "sparse_matrix.h"
#include <stdlib.h>

typedef struct
{
    size_t size;
    int *nonZero;
    size_t *columnIndex;
    size_t *rowIndex;
} SparseVector;
