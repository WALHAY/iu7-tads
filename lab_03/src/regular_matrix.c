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

void free_regular_matrix(RegularMatrix *matrix)
{
    if (!matrix)
        return;

    if (matrix->buffer)
        free(matrix->buffer);

    if (matrix->matrix)
        free(matrix->matrix);

    free(matrix);
}

int generate_random_regular_matrix(RegularMatrix *matrix, float fill)
{
    if (!matrix)
        return NULLPTR_ERROR;

    size_t elements = matrix->rows * matrix->columns;
    size_t fill_elements = ceil(elements * fill);
    size_t indices[elements];
    for (size_t i = 0; i < elements; ++i)
        indices[i] = i;

    for (size_t i = 0; i < fill_elements; ++i)
    {
        size_t arr_index = rand() % elements--;
        size_t index = indices[arr_index];

        size_t row = index / matrix->columns;
        size_t column = index % matrix->columns;
        int value = (rand() % 100) * (rand() % 2 ? -1 : 1);
        matrix->matrix[row][column] = value;

        indices[arr_index] = indices[elements];
    }
    return SUCCESS;
}

RegularMatrix *from_sparse_to_regular_matrix(SparseMatrix *matrix)
{
    RegularMatrix *result = create_regular_matrix(matrix->rows, matrix->columns);
    for (size_t column = 0; column < matrix->columns; ++column)
    {
        size_t columnStart = matrix->columnStartIndex[column];
        size_t columnEnd = matrix->columnStartIndex[column + 1];
        for (size_t j = columnStart; j < columnEnd; ++j)
        {
            int value = matrix->elements[j];
            size_t row = matrix->rowIndex[j];
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
