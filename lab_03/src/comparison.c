#include "../inc/comparison.h"

#define TRY 50

void compare_multiplication_time(size_t rows, size_t columns, float fill)
{
    struct timespec t1, t2;
    long long sparse = 0;
    long long regular = 0;
    for (size_t i = 0; i < TRY; ++i)
    {
        SparseVector *vector = create_vector(rows, 0);
        SparseMatrix *matrix = create_matrix(rows, columns, 0);
        SparseVector *result = create_vector(rows, rows);
        generate_random_vector(vector, 1.0f);
        generate_random_matrix(matrix, fill);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        multiply_vector_by_matrix(vector, matrix, result);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        sparse += difftime(t2.tv_nsec, t1.tv_nsec) + 1000000000 * difftime(t2.tv_sec, t1.tv_sec);

        generate_random_vector(vector, 1.0f);
        generate_random_matrix(matrix, fill);
        RegularVector *rvector = from_sparse_to_regular_vector(vector);
        RegularMatrix *rmatrix = from_sparse_to_regular_matrix(matrix);
        RegularVector *rresult = create_regular_vector(rvector->length);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        multiply_vector_by_matrix_basic(rvector, rmatrix, rresult);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        regular += difftime(t2.tv_nsec, t1.tv_nsec) + 1000000000 * difftime(t2.tv_sec, t1.tv_sec);
        free_regular_vector(rresult);
        free_regular_vector(rvector);
        free_regular_matrix(rmatrix);
        free_matrix(matrix);
        free_vector(vector);
    }
    long long avg_sparse = sparse / TRY;
    long long avg_regular = regular / TRY;
    printf("%lld\t%lld\n", avg_regular, avg_sparse);
}

void compare_matrix_memory(size_t rows, size_t columns, float fill)
{
    size_t regular_size = sizeof(RegularMatrix) + rows * columns * sizeof(int);
    SparseMatrix *matrix = create_matrix(rows, columns, 0);
    generate_random_matrix(matrix, fill);
    size_t sparse_size =
        sizeof(SparseMatrix) + matrix->size * (sizeof(int) + sizeof(size_t)) + (matrix->rows + 1) * sizeof(size_t);

    printf("Matrix %zu %zu with fill %d%% = %zu(regular), %zu(sparse)\n", rows, columns, (int)(fill * 100),
           regular_size, sparse_size);
}

void compare_vector_memory(size_t length, float fill)
{
    size_t regular_size = sizeof(RegularVector) + length * sizeof(int);

    size_t elements = length * fill;
    size_t sparse_size = sizeof(SparseVector) + elements * (sizeof(int) + sizeof(size_t));
    printf("Vector %zu with fill %d%% = %zu(regular), %zu(sparse)\n", length, (int)(fill * 100), regular_size,
           sparse_size);
}

void compare_tads(void)
{
    printf("Compare matrix multiplication time\n");
    for (float i = 0; i <= 1.0f; i += 0.1f)
        compare_multiplication_time(30, 30, i);

    printf("\nCompare matrix memory\n");
    for (float i = 0; i <= 1.0f; i += 0.05f)
        compare_matrix_memory(30, 30, i);

    printf("\nCompare vectory memory\n");
    for (float i = 0; i <= 1.0f; i += 0.05f)
        compare_vector_memory(30, i);
}
