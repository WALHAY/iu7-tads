#pragma once

#include "regular_matrix.h"
#include "regular_vector.h"
#include "sparse_matrix.h"
#include "sparse_vector.h"

SparseVector *multiply_vector_by_matrix(SparseVector *vector, SparseMatrix *matrix);

RegularVector *multiply_vector_by_matrix_basic(RegularVector *vector, RegularMatrix *matrix);
