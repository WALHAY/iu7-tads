#pragma once

#include "regular_matrix.h"
#include "regular_vector.h"
#include "sparse_matrix.h"
#include "sparse_vector.h"

void multiply_vector_by_matrix(SparseVector *vector, SparseMatrix *matrix, SparseVector *result);

void multiply_vector_by_matrix_basic(RegularVector *vector, RegularMatrix *matrix, RegularVector *result);
