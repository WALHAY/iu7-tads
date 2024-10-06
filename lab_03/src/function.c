#include "../inc/functions.h"

SparseMatrix *multiply_matrix_on_vector(SparseMatrix *matrix, SparseVector *vector)
{
    if (!matrix || !vector)
        return NULL;

    SparseMatrix *result = create_matrix(matrix->rows, matrix->columns, matrix->size);

    if (!result)
        return NULL;

    for (size_t row = 0; row < matrix->rows; ++row)
    {
        int sum = 0;
        for (size_t start = matrix->rowStartIndex[row]; start < matrix->rowStartIndex[row + 1]; ++start)
        {
            size_t column = matrix->columnIndex[start];

            for (size_t vectorRow = 0; vectorRow < vector->size; ++vectorRow)
            {
                if (vector->index[vectorRow] > column)
                    break;
                else if (vector->index[vectorRow] < column)
                    continue;
                else
                    sum += vector->elements[vectorRow] * matrix->elements[start];
            }
        }
    }

    return result;
}
