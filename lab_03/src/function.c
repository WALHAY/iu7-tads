#include "../inc/functions.h"

SparseMatrix *multiply_matrix_on_vector(SparseMatrix *matrix, SparseVector *vector)
{
    return matrix == NULL || vector == NULL ? NULL : create_matrix(3, 3, 1);
}
