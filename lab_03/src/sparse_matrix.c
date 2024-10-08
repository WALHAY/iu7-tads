#include "../inc/sparse_matrix.h"

SparseMatrix *create_matrix(size_t rows, size_t columns, size_t initial_size)
{
    SparseMatrix *matrix = malloc(sizeof(SparseMatrix));
    if (!matrix)
        return NULL;

    matrix->size = 0;
    matrix->elements = calloc(initial_size, sizeof(int));
    matrix->columnIndex = calloc(initial_size, sizeof(size_t));
    matrix->rowStartIndex = calloc(rows + 1, sizeof(size_t));
    matrix->rows = rows;
    matrix->columns = columns;

    return matrix;
}

SparseMatrix *free_matrix(SparseMatrix *matrix)
{
    if (!matrix)
        return NULL;

    if (!matrix->elements)
        free(matrix->elements);

    if (!matrix->columnIndex)
        free(matrix->columnIndex);

    if (!matrix->rowStartIndex)
        free(matrix->rowStartIndex);
    free(matrix);
    return NULL;
}

int add_matrix_element(SparseMatrix *matrix, int element, size_t row, size_t column)
{
    if (!matrix)
        return NULLPTR_ERROR;

    if (row >= matrix->rows || column >= matrix->columns)
        return WRONG_POS_ERROR;

    matrix->elements = realloc(matrix->elements, sizeof(int) * (matrix->size + 1));
    matrix->columnIndex = realloc(matrix->columnIndex, sizeof(size_t) * (matrix->size + 1));

    size_t rowStart = matrix->rowStartIndex[row];
    size_t rowEnd = matrix->rowStartIndex[row + 1];
    // keep it ordered
    for (; rowStart < rowEnd; ++rowStart)
        if (matrix->columnIndex[rowStart] > column)
            break;
        else if (matrix->columnIndex[rowStart] == column)
            return ELEMENT_EXIST_ERROR;

    for (size_t i = matrix->size; i >= rowStart && i >= 1; --i)
    {
        matrix->elements[i] = matrix->elements[i - 1];
        matrix->columnIndex[i] = matrix->columnIndex[i - 1];
    }
    matrix->elements[rowStart] = element;
    matrix->columnIndex[rowStart] = column;
    matrix->size++;

    for (size_t i = row + 1; i <= matrix->rows; ++i)
        matrix->rowStartIndex[i]++;

    return SUCCESS;
}

int replace_matrix_element(SparseMatrix *matrix, int element, size_t row, size_t column)
{
    if (!matrix)
        return NULLPTR_ERROR;

    if (row >= matrix->rows || column >= matrix->columns)
        return WRONG_POS_ERROR;

    size_t rowStart = matrix->rowStartIndex[row];
    size_t rowEnd = matrix->rowStartIndex[row + 1];

    for (size_t i = rowStart; i < rowEnd && matrix->columnIndex[i] <= column; ++i)
    {
        if (matrix->columnIndex[i] == column)
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

        for (size_t j = arr_index; j < elements; ++j)
            indices[j] = indices[j + 1];
    }
    return SUCCESS;
}

static void print_full_matrix(SparseMatrix *matrix)
{
    for (size_t i = 0; i < matrix->rows; ++i)
    {
        size_t current_index = 0;
        size_t start = matrix->rowStartIndex[i];
        size_t end = matrix->rowStartIndex[i + 1];

        for (size_t j = start; j < end; ++j)
        {
            while (current_index++ < matrix->columnIndex[j])
                printf("0\t");
            printf("%d\t", matrix->elements[j]);
        }

        while (current_index++ < matrix->columns)
            printf("0\t");
        printf("\n");
    }
}

static void print_short_matrix(SparseMatrix *matrix)
{
    printf("A: ");
    for (size_t i = 0; i < matrix->size; ++i)
        printf("%d\t", matrix->elements[i]);
    printf("\n");

    printf("JA: ");
    for (size_t i = 0; i < matrix->rows; ++i)
        for (size_t j = matrix->rowStartIndex[i]; j < matrix->rowStartIndex[i + 1]; ++j)
            printf("%zu\t", matrix->columnIndex[j]);
    printf("\n");

    printf("IA: ");
    for (size_t i = 0; i <= matrix->rows; ++i)
        printf("%zu\t", matrix->rowStartIndex[i]);
    printf("\n");
}

int print_sparse_matrix(SparseMatrix *matrix)
{
    if (!matrix)
        return NULLPTR_ERROR;

    if (matrix->columns > 30 || matrix->rows > 30)
        print_short_matrix(matrix);
    else
        print_full_matrix(matrix);
    return SUCCESS;
}
