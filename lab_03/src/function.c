#include "../inc/functions.h"

void multiply_vector_by_matrix(SparseVector *vector, SparseMatrix *matrix, SparseVector *result)
{
    if (!matrix || !vector || !result)
        return;

    if (matrix->rows != vector->length)
        return;
}

void multiply_vector_by_matrix_basic(RegularVector *vector, RegularMatrix *matrix, RegularVector *result)
{
    if (!vector || !matrix || !result)
        return;

    if (vector->length != matrix->rows)
        return;

    for (size_t column = 0; column < vector->length; ++column)
    {
        int sum = 0;
        for (size_t i = 0; i < vector->length; ++i)
            sum += vector->data[i] * matrix->matrix[i][column];
        result->data[column] = sum;
    }
}
