#include "../inc/sparse_vector.h"

SparseVector *create_vector(size_t length, size_t initial_size)
{
    SparseVector *vector = malloc(sizeof(SparseVector));
    if (!vector)
        return NULL;

    vector->length = length;
    vector->size = 0;
    vector->elements = malloc(sizeof(int) * initial_size);
    vector->index = calloc(initial_size, sizeof(size_t));

    return vector;
}

int add_vector_element(SparseVector *vector, int element, size_t index)
{
    if (!vector)
        return NULLPTR_ERROR;

    if (index >= vector->length)
        return WRONG_POS_ERROR;

    vector->elements = realloc(vector->elements, sizeof(int) * (vector->size + 1));
    vector->index = realloc(vector->index, sizeof(size_t) * (vector->size + 1));

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

int replace_vector_element(SparseVector *vector, int element, size_t index)
{
    if (!vector)
        return NULLPTR_ERROR;

    if (index > vector->length)
        return WRONG_POS_ERROR;

    for (size_t i = 0; i < vector->size && vector->index[i] > index; ++i)
    {
        if (vector->index[i] == index)
        {
            vector->elements[i] = element;
            return SUCCESS;
        }
    }

    return REPLACE_ERROR;
}

void generate_random_vector(SparseVector *vector, float fill)
{
    size_t elements = vector->length;
    size_t fill_elements = elements * fill;
    int indices[elements];

    for (size_t i = 0; i < elements; ++i)
        indices[i] = i;

    for (size_t i = 0; i < fill_elements; ++i)
    {
        size_t arr_index = rand() % elements--;
        size_t index = indices[arr_index];
        int value = (rand() % 100) * (rand() % 2 ? -1 : 1);
        add_vector_element(vector, value, index);

        for (size_t j = arr_index; j < elements; ++j)
            indices[j] = indices[j + 1];
    }
}

static void print_full_vector(SparseVector *vector)
{
    size_t current_index = 0;
    for (size_t i = 0; i < vector->size; ++i)
    {
        while (current_index++ < vector->index[i])
            printf("0\t");
        printf("%d\t", vector->elements[i]);
    }
    while (current_index++ < vector->length)
        printf("0\t");
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

    if (vector->length <= 30)
        print_full_vector(vector);
    else
        print_short_vector(vector);
}
