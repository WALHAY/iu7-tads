#include "../inc/functions.h"

void multiply_vector_by_matrix(SparseVector *vector, SparseMatrix *matrix, SparseVector *result)
{
    if (!matrix || !vector || !result)
        return;

    if (matrix->rows != vector->length)
        return;

    for (size_t column = 0; column < matrix->columns; ++column)
    {
        size_t rowStart = matrix->columnStartIndex[column];
        size_t rowEnd = matrix->columnStartIndex[column + 1];
        int sum = 0;
        size_t index = 0;
        for (size_t pos = rowStart; pos < rowEnd; ++pos)
        {
            int value = matrix->elements[pos];
            size_t row = matrix->rowIndex[pos];
            while (index < vector->size && vector->index[index] < row)
                index++;

            if (vector->index[index] == row)
                sum += vector->elements[index] * value;
        }

        if (sum)
            add_vector_element(result, sum, column);
    }
}

void multiply_vector_by_matrix_basic(RegularVector *vector, RegularMatrix *matrix, RegularVector *result)
{
    if (!vector || !matrix || !result)
        return;

    if (vector->length != matrix->rows)
        return;

    for (size_t column = 0; column < matrix->columns; ++column)
    {
        int sum = 0;
        for (size_t row = 0; row < matrix->rows; ++row)
            sum += vector->data[row] * matrix->matrix[row][column];
        result->data[column] = sum;
    }
}
