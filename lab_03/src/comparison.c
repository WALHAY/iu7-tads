#include "../inc/comparison.h"

static void compare_multiplication_time(size_t rows, size_t columns, float fill, FILE *out)
{
    size_t regular = 0;
    size_t sparse = 0;
    struct timespec t1, t2;
    for (size_t i = 0; i < TRY; ++i)
    {
        SparseVector *vector = create_vector(rows, 0);
        SparseMatrix *matrix = create_matrix(rows, columns, 0);
        SparseVector *result = create_vector(rows, rows);
        generate_random_vector(vector, fill);
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
    long long sparse_avg = sparse / TRY;
    long long regular_avg = regular / TRY;
    float boost = (regular_avg - sparse_avg) * 100.0f / regular_avg;
    fprintf(out, "%zu:\t\t%lld\t%lld\t%.1f%%\n", rows, regular_avg, sparse_avg, boost);
}

static void compare_matrix_memory(size_t rows, size_t columns, float fill, FILE *out)
{
    long long regular_size = sizeof(RegularMatrix) + rows * columns * sizeof(int);
    long long elements = ceil((rows * columns) * fill);
    long long sparse_size = sizeof(SparseMatrix) + elements * sizeof(int) + (elements + columns + 1) * sizeof(size_t);

    float boost = (regular_size - sparse_size) * 100.0f / regular_size;
    fprintf(out, "%zu:\t\t%lld\t%lld\t%.1f%%\n", rows, regular_size, sparse_size, boost);
}

static void compare_vector_memory(size_t length, float fill, FILE *out)
{
    long long regular_size = sizeof(RegularVector) + length * sizeof(int);

    long long elements = ceil(length * fill);
    long long sparse_size = sizeof(SparseVector) + elements * (sizeof(int) + sizeof(size_t));
    float boost = (regular_size - sparse_size) * 100.0f / regular_size;
    fprintf(out, "%zu:\t\t%lld\t%lld\t%.1f%%\n", length, regular_size, sparse_size, boost);
}

static void compare_multiplication_memory(size_t rows, size_t columns, float fill, FILE *out)
{
    long long regular_size =
        sizeof(RegularVector) + rows * sizeof(int) + sizeof(RegularMatrix) + rows * columns * sizeof(int);

    long long matrix_elements = ceil((rows * columns) * fill);
    long long vector_elements = ceil(rows * fill);
    long long sparse_size = sizeof(SparseVector) + vector_elements * (sizeof(int) + sizeof(size_t)) +
                            sizeof(SparseMatrix) + matrix_elements * (sizeof(int) + sizeof(size_t)) +
                            (columns + 1) * sizeof(size_t);
    float boost = (regular_size - sparse_size) * 100.0f / regular_size;
    fprintf(out, "%zu:\t\t%lld\t%lld\t%.1f%%\n", rows, regular_size, sparse_size, boost);
}

void multiplication_time_comparison(void)
{
    printf("Time comparison\n");
    for (int i = 1; i <= 20; i++)
    {
        printf("\nFill %d%%\n", i);
        printf("Elements:\tRegular\tSparse\tBoost\n");
        compare_multiplication_time(10, 10, i / 100.0f, stdout);
        compare_multiplication_time(50, 50, i / 100.0f, stdout);
        compare_multiplication_time(500, 500, i / 100.0f, stdout);
    }
}

void multiplication_memory_comparison(void)
{
    printf("Algorithm memory comparison\n");
    for (int i = 5; i <= 50; i += 5)
    {
        printf("\nFill %d%%\n", i);
        printf("Elements:\tRegular\tSparse\tBoost\n");
        compare_multiplication_memory(10, 10, i / 100.0f, stdout);
        compare_multiplication_memory(50, 50, i / 100.0f, stdout);
        compare_multiplication_memory(500, 500, i / 100.0f, stdout);
    }
}

void matrix_memory_comparsion(void)
{
    printf("Matrix Memory comparison\n");
    for (int i = 5; i <= 50; i += 5)
    {
        printf("\nFill %d%%\n", i);
        printf("Elements:\tRegular\tSparse\tBoost\n");
        compare_matrix_memory(10, 10, i / 100.0f, stdout);
        compare_matrix_memory(50, 50, i / 100.0f, stdout);
        compare_matrix_memory(500, 500, i / 100.0f, stdout);
    }
}

void vector_memory_comparsion(void)
{
    printf("Vector Memory comparison\n");
    for (int i = 5; i <= 50; i += 5)
    {
        printf("\nFill %d%%\n", i);
        printf("Elements:\tRegular\tSparse\tBoost\n");
        compare_vector_memory(10, i / 100.0f, stdout);
        compare_vector_memory(50, i / 100.0f, stdout);
        compare_vector_memory(500, i / 100.0f, stdout);
    }
}

void collect_all_data_to_file(FILE *file)
{
    fprintf(file, "Multiplication time comparison\n");
    for (float f = 0.05f; f <= 0.501f; f += 0.05f)
        compare_multiplication_memory(10, 10, f, file);
    fflush(file);
    for (float f = 0.05f; f <= 0.501f; f += 0.05f)
        compare_multiplication_memory(50, 50, f, file);
    fflush(file);
    for (float f = 0.05f; f <= 0.501f; f += 0.05f)
        compare_multiplication_memory(500, 500, f, file);
    fflush(file);

    fprintf(file, "Multiplication time comparison\n");
    for (float f = 0.01f; f <= 0.201f; f += 0.01f)
        compare_multiplication_time(10, 10, f, file);
    fflush(file);
    for (float f = 0.01f; f <= 0.151f; f += 0.01f)
        compare_multiplication_time(50, 50, f, file);
    fflush(file);
    for (float f = 0.01f; f <= 0.151f; f += 0.01f)
        compare_multiplication_time(500, 500, f, file);
    fflush(file);
}
