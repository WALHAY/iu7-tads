#include "../inc/sparse_vector.h"

SparseVector *create_vector(size_t length)
{
    SparseVector *vector = malloc(sizeof(SparseVector));
    if (!vector)
        return NULL;

    vector->length = length;
    vector->size = 0;
    vector->elements = malloc(sizeof(int) * length);
    vector->index = calloc(length, sizeof(size_t));

    return vector;
}

int add_vector_element(SparseVector *vector, int element, size_t index)
{
    if (!vector)
        return NULLPTR_ERROR;

    if (index >= vector->length)
        return WRONG_POS_ERROR;

    size_t insert_at = 0;
    for (; insert_at < vector->size; ++insert_at)
        if (vector->index[insert_at] > index)
            break;
        else if (vector->index[insert_at] == index)
            return ELEMENT_EXIST_ERROR;

    for (size_t move = vector->size; move >= insert_at && move >= 1; --move)
    {
        vector->elements[move] = vector->elements[move - 1];
        vector->index[move] = vector->index[move - 1];
    }
    vector->index[insert_at] = index;
    vector->elements[insert_at] = element;
    vector->size++;

    return SUCCESS;
}

void generate_random_vector(SparseVector *vector, size_t elements);

int get_or_zero(SparseVector *vector, size_t index)
{
    if (index >= vector->size)
        return 0;

    for (size_t i = 0; i < vector->size; ++i)
        if (vector->index[i] == index)
            return vector->elements[i];

    return 0;
}

static void print_full_vector(SparseVector *vector)
{
    size_t current_index = 0;
    for (size_t i = 0; i < vector->size; ++i)
    {
        while (current_index++ < vector->index[i])
            printf("0\t");
        printf("%d\t", vector->elements[i]);
        current_index++;
    }
    printf("\n");
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

    if (vector->size <= 30)
        print_full_vector(vector);
    else
        print_short_vector(vector);
}
