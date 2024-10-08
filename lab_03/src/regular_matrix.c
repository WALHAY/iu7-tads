#include "../inc/regular_matrix.h"

RegularMatrix *create_regular_matrix(size_t rows, size_t columns)
{
    RegularMatrix *result = malloc(sizeof(RegularMatrix));
    result->rows = rows;
    result->columns = columns;
    result->matrix = malloc(sizeof(int *) * rows);
    result->buffer = calloc(rows * columns, sizeof(int));
    for (size_t row = 0; row < rows; ++row)
        result->matrix[row] = result->buffer + row * columns;
    return result;
}

RegularMatrix *from_sparse_to_regular_matrix(SparseMatrix *matrix)
{
    RegularMatrix *result = create_regular_matrix(matrix->rows, matrix->columns);
    for (size_t row = 0; row < matrix->rows; ++row)
    {
        size_t rowStart = matrix->rowStartIndex[row];
        size_t rowEnd = matrix->rowStartIndex[row + 1];
        for (size_t index = rowStart; index < rowEnd; ++index)
        {
            size_t column = matrix->columnIndex[index];
            int value = matrix->elements[index];
            result->matrix[row][column] = value;
        }
    }
    return result;
}

SparseMatrix *from_regular_to_sparse_matrix(RegularMatrix *matrix)
{
    SparseMatrix *result = create_matrix(matrix->rows, matrix->columns, 0);

    for (size_t row = 0; row < matrix->rows; ++row)
    {
        for (size_t column = 0; column < matrix->columns; ++column)
        {
            int value = matrix->matrix[row][column];
            if (value)
                add_matrix_element(result, value, row, column);
        }
    }

    return result;
}
