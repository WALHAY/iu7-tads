#include "../inc/sparse_vector.h"

SparseVector *create_vector(size_t size)
{
    SparseVector *vector = malloc(sizeof(SparseVector));
    if (!vector)
        return NULL;

    vector->elements = malloc(sizeof(int) * size);

    return vector;
}

void generate_random_vector(SparseVector *vector, size_t elements);

static void print_full_vector(SparseVector *vector)
{
    size_t current_index = 0;
    for (size_t i = 0; i < vector->size; ++i)
    {
        while (current_index < vector->index[i])
            printf("0\t");
        printf("\n");
    }
}

static void print_short_vector(SparseVector *vector)
{
    printf("B: ");
    for (size_t i = 0; i < vector->size; ++i)
        printf("%d\t", vector->elements[i]);
    printf("\n");
    printf("JB: ");
    for (size_t i = 0; i < vector->size; ++i)
        printf("%zu\t", vector->index[i]);
    printf("\n");
}

void print_sparse_vector(SparseVector *vector)
{
    if (!vector)
        return;

    if (vector->size > 30)
        print_full_vector(vector);
    else
        print_short_vector(vector);
}
