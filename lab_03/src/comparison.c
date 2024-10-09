#include "../inc/comparison.h"

void compare_multiplication_time(size_t rows, size_t columns, float fill)
{
    size_t regular = 0;
    size_t sparse = 0;
    struct timespec t1, t2;
    for (size_t i = 0; i < TRY; ++i)
    {
        SparseVector *vector = create_vector(rows, 0);
        SparseMatrix *matrix = create_matrix(rows, columns, 0);
        SparseVector *result = create_vector(rows, 0);
        generate_random_vector(vector, 0.9f);
        generate_random_matrix(matrix, fill);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        multiply_vector_by_matrix(vector, matrix, result);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        sparse += difftime(t2.tv_sec, t1.tv_sec) * 1000000000 + difftime(t2.tv_nsec, t1.tv_nsec);

        RegularVector *rvector = create_regular_vector(rows);
        RegularMatrix *rmatrix = create_regular_matrix(rows, columns);
        RegularVector *rresult = create_regular_vector(rows);

        generate_random_regular_vector(rvector, fill);
        generate_random_regular_matrix(rmatrix, fill);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        multiply_vector_by_matrix_basic(rvector, rmatrix, rresult);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        regular += difftime(t2.tv_sec, t1.tv_sec) * 1000000000 + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    size_t sparse_avg = sparse / TRY;
    size_t regular_avg = regular / TRY;
    printf("%zu:\t\t%zu\t%zu\n", rows, regular_avg, sparse_avg);
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
    for (float i = 0.01f; i <= 0.251f; i += 0.01f)
    {
        printf("\nFill %d%%\n", (int)(i * 100));
        printf("Elements:\tRegular\tSparse\n");
        compare_multiplication_time(10, 10, i);
        compare_multiplication_time(50, 50, i);
        compare_multiplication_time(100, 100, i);
    }
}
