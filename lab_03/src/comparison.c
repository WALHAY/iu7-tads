#include "../inc/comparison.h"

#define TRY 50

void compare_multiplication_time(size_t rows, size_t columns, float fill)
{
    struct timespec t1, t2;
    size_t sparse = 0;
    size_t regular = 0;
    for (size_t i = 0; i < TRY; ++i)
    {
        SparseVector *vector = create_vector(rows, 0);
        SparseMatrix *matrix = create_matrix(rows, columns, 0);
        SparseVector *result = create_vector(rows, 0);
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
    }
    size_t avg_sparse = sparse / TRY;
    size_t avg_regular = regular / TRY;
    printf("%zu\t%zu\n", avg_regular, avg_sparse);
}

void compare_matrix_memory(size_t rows, size_t columns, float fill);

void compare_vector_memory(size_t length, float fill);

void compare_tads()
{
    for (float i = 0; i < 1.0f; i += 0.1f)
    {
        compare_multiplication_time(100, 100, i);
    }
}
