#include "../inc/functions.h"

SparseVector *multiply_vector_by_matrix(SparseVector *vector, SparseMatrix *matrix)
{
    if (!matrix || !vector)
        return NULL;

    if (matrix->columns != vector->length)
        return NULL;

    SparseVector *result = create_vector(vector->length, 0);

    for (size_t i = 0; i < vector->size; ++i)
    {
        int sum = 0;
        size_t column = vector->index[i];
        size_t rowStart = matrix->rowStartIndex[column];
        size_t rowEnd = matrix->rowStartIndex[column + 1];
        for (size_t j = rowStart; j < rowEnd && matrix->columnIndex[j] <= column; ++j)
        {
            if (matrix->columnIndex[j] == column)
                sum += matrix->elements[j] * vector->elements[column];
        }
        add_vector_element(result, sum, column);
    }

    if (!result)
        return NULL;

    return result;
}
