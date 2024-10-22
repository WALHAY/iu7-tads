#include "../inc/sparse_matrix.h"

#define MAX(a, b) ((a > b) ? a : b)

SparseMatrix *create_matrix(size_t rows, size_t columns, size_t initial_size)
{
    SparseMatrix *matrix = malloc(sizeof(SparseMatrix));
    if (!matrix)
        return NULL;

    matrix->allocated = initial_size;
    matrix->size = 0;
    matrix->elements = calloc(initial_size, sizeof(int));
    matrix->rowIndex = calloc(initial_size, sizeof(size_t));
    matrix->columnStartIndex = calloc(columns + 1, sizeof(size_t));
    matrix->rows = rows;
    matrix->columns = columns;

    return matrix;
}

void free_matrix(SparseMatrix *matrix)
{
    if (!matrix)
        return;

    if (matrix->elements)
        free(matrix->elements);

    if (matrix->rowIndex)
        free(matrix->rowIndex);

    if (matrix->columnStartIndex)
        free(matrix->columnStartIndex);
    free(matrix);
}

int add_matrix_element(SparseMatrix *matrix, int element, size_t row, size_t column)
{
    if (!element)
        return ZERO_ADD;

    if (!matrix)
        return NULLPTR_ERROR;

    if (row >= matrix->rows || column >= matrix->columns)
        return WRONG_POS_ERROR;

    if (matrix->size + 1 > matrix->allocated)
    {
        matrix->elements = realloc(matrix->elements, sizeof(int) * (matrix->size + 1));
        matrix->rowIndex = realloc(matrix->rowIndex, sizeof(size_t) * (matrix->size + 1));
        matrix->allocated++;
    }

    size_t columnStart = matrix->columnStartIndex[column];
    size_t columnEnd = matrix->columnStartIndex[column + 1];
    // keep it ordered
    for (; columnStart < columnEnd; ++columnStart)
        if (matrix->rowIndex[columnStart] > row)
            break;
        else if (matrix->rowIndex[columnStart] == row)
            return ELEMENT_EXIST_ERROR;

    for (size_t i = matrix->size; i >= columnStart && i >= 1; --i)
    {
        matrix->elements[i] = matrix->elements[i - 1];
        matrix->rowIndex[i] = matrix->rowIndex[i - 1];
    }
    matrix->elements[columnStart] = element;
    matrix->rowIndex[columnStart] = row;
    matrix->size++;

    for (size_t i = column + 1; i <= matrix->columns; ++i)
        matrix->columnStartIndex[i]++;

    return SUCCESS;
}

int replace_matrix_element(SparseMatrix *matrix, int element, size_t row, size_t column)
{
    if (!matrix)
        return NULLPTR_ERROR;

    if (row >= matrix->rows || column >= matrix->columns)
        return WRONG_POS_ERROR;

    size_t columnStart = matrix->columnStartIndex[column];
    size_t columnEnd = matrix->columnStartIndex[column + 1];

    for (size_t i = columnStart; i < columnEnd && matrix->rowIndex[i] <= row; ++i)
    {
        if (matrix->rowIndex[i] == row)
        {
            matrix->elements[i] = element;
            return SUCCESS;
        }
    }

    return REPLACE_ERROR;
}

int generate_random_matrix(SparseMatrix *matrix, float fill)
{
    if (!matrix)
        return NULLPTR_ERROR;

    size_t elements = matrix->rows * matrix->columns;
    size_t fill_elements = elements * fill;
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
        if (add_matrix_element(matrix, value, row, column) == ELEMENT_EXIST_ERROR)
            replace_matrix_element(matrix, value, row, column);

        indices[arr_index] = indices[elements];
    }
    return SUCCESS;
}

static void print_full_matrix(SparseMatrix *matrix)
{
    for (size_t row = 0; row < matrix->rows; ++row)
    {
        for (size_t column = 0; column < matrix->columns; ++column)
        {
            size_t columnStart = matrix->columnStartIndex[column];
            size_t columnEnd = matrix->columnStartIndex[column + 1];

            int value = 0;
            bool found = false;
            for (size_t pos = columnStart; pos < columnEnd; ++pos)
            {
                if (matrix->rowIndex[pos] == row)
                {
                    found = true;
                    value = matrix->elements[pos];
                    break;
                }
            }

            printf("%d\t", found ? value : 0);
        }
        printf("\n");
    }
}

static void print_short_matrix(SparseMatrix *matrix)
{
    printf("A:  ");
    for (size_t i = 0; i < matrix->size; ++i)
        printf("%d\t", matrix->elements[i]);
    printf("\n");
    printf("IA: ");
    for (size_t column = 0; column < matrix->columns; ++column)
        for (size_t pos = matrix->columnStartIndex[column]; pos < matrix->columnStartIndex[column + 1]; ++pos)
            printf("%zu\t", matrix->rowIndex[pos]);
    printf("\n");
    printf("JA: ");
    for (size_t i = 0; i <= matrix->columns; ++i)
        printf("%zu\t", matrix->columnStartIndex[i]);
    printf("\n");
}

int print_sparse_matrix(SparseMatrix *matrix)
{
    if (!matrix)
    {
        printf("\nError: Matrix not specified!\n");
        return NULLPTR_ERROR;
    }

    printf("\nMatrix:\n");
    if (matrix->columns < 30 && matrix->rows < 30)
        print_full_matrix(matrix);

    printf("\nSparse format:\n");
    print_short_matrix(matrix);
    return SUCCESS;
}
