#include "../inc/functions.h"

SparseVector *multiply_vector_by_matrix(SparseVector *vector, SparseMatrix *matrix)
{
    if (!matrix || !vector)
        return NULL;

    if (matrix->columns != vector->length)
        return NULL;

    SparseVector *result = create_vector(vector->length, 0);

    for (size_t i = 0; i < matrix->columns; ++i)
    {
        int sum = 0;
        for (size_t index = 0; index < vector->size; ++index)
        {
            size_t column = vector->index[index];
            size_t rowStart = matrix->rowStartIndex[column];
            size_t rowEnd = matrix->rowStartIndex[column + 1];
            for (size_t j = rowStart; j < rowEnd; ++j)
                if (matrix->columnIndex[j] == i)
                    sum += matrix->elements[j] * vector->elements[index];
        }
        add_vector_element(result, sum, i);
    }

    if (!result)
        return NULL;

    return result;
}

RegularVector *multiply_vector_by_matrix_basic(RegularVector *vector, RegularMatrix *matrix)
{
    RegularVector *result = create_regular_vector(vector->length);
    for (size_t column = 0; column < vector->length; ++column)
    {
        int sum = 0;
        for (size_t i = 0; i < vector->length; ++i)
            sum += vector->data[i] * matrix->matrix[i][column];
        result->data[column] = sum;
    }
    return result;
}
