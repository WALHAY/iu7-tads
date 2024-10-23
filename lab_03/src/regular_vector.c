#include "../inc/regular_vector.h"

RegularVector *create_regular_vector(size_t length)
{
    RegularVector *result = malloc(sizeof(RegularVector));
    result->length = length;
    result->data = calloc(length, sizeof(int));
    return result;
}

void free_regular_vector(RegularVector *vector)
{
    if (!vector)
        return;

    if (vector->data)
        free(vector->data);
    free(vector);
}

int generate_random_regular_vector(RegularVector *vector, float fill)
{
    if (!vector)
        return NULLPTR_ERROR;

    size_t elements = vector->length;
    size_t fill_elements = ceil(elements * fill);
    size_t indices[elements];
    for (size_t i = 0; i < elements; ++i)
        indices[i] = i;

    for (size_t i = 0; i < fill_elements; ++i)
    {
        size_t arr_index = rand() % elements--;
        int value = (rand() % 100) * (rand() % 2 ? -1 : 1);
        vector->data[indices[arr_index]] = value;

        indices[arr_index] = indices[elements];
    }
    return SUCCESS;
}

RegularVector *from_sparse_to_regular_vector(SparseVector *vector)
{
    RegularVector *result = create_regular_vector(vector->length);
    size_t current_index = 0;
    for (size_t i = 0; i < vector->size; ++i)
    {
        size_t index = vector->index[i];
        int value = vector->elements[i];
        while (current_index < index)
            result->data[current_index++] = 0;
        result->data[current_index++] = value;
    }
    return result;
}

SparseVector *from_regular_to_sparse_vector(RegularVector *vector)
{
    SparseVector *result = create_vector(vector->length, 0);
    for (size_t i = 0; i < vector->length; ++i)
    {
        int value = vector->data[i];
        if (value)
            add_vector_element(result, value, i);
    }

    return result;
}

int fit_to_size(SparseVector *vector)
{
    if (!vector)
        return NULLPTR_ERROR;

    if (vector->size < vector->allocated)
    {
        int *new_ptr = realloc(vector->elements, vector->size * sizeof(int));
        if (!new_ptr)
            return ALLOC_ERROR;
        vector->elements = new_ptr;
    }
    return SUCCESS;
}
