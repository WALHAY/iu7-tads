#include "../inc/sparse_matrix.h"

SparseMatrix *create_matrix(size_t rows, size_t columns, size_t elements)
{
    SparseMatrix *matrix = malloc(sizeof(SparseMatrix));
    if (!matrix)
        return NULL;

    matrix->size = 0;
    matrix->elements = malloc(sizeof(int) * elements);
    matrix->columnIndex = calloc(sizeof(int), elements);
    matrix->rowStartIndex = calloc(sizeof(int *), rows + 1);
    matrix->rows = rows;
    matrix->columns = columns;

    return matrix;
}

int input_matrix(SparseMatrix *matrix)
{
    return !matrix ? NULLPTR_ERROR : SUCCESS;
}

int add_matrix_element(SparseMatrix *matrix, int element, size_t row, size_t column)
{
    if (!matrix)
        return NULLPTR_ERROR;

    if (row >= matrix->rows || column >= matrix->columns)
        return WRONG_POS_ERROR;

    size_t rowStart = matrix->rowStartIndex[row];
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

int generate_random_matrix(SparseMatrix *matrix, size_t elements)
{
    srand(time(NULL));
    for (size_t i = 0; i < elements; ++i)
    {
        size_t row = rand() % matrix->rows;
        size_t column = rand() % matrix->columns;
        add_matrix_element(matrix, rand() % 100 * (rand() % 2 ? -1 : 1), row, column);
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

        for (; current_index < matrix->columns; ++current_index)
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
    for (size_t i = 0; i < matrix->columns; ++i)
        printf("%zu\t", matrix->rowStartIndex[i]);
    printf("\n");
}

int print_sparse_matrix(SparseMatrix *matrix)
{
    if (matrix->columns > 30 || matrix->rows > 30)
        print_short_matrix(matrix);
    else
        print_full_matrix(matrix);
    return SUCCESS;
}
