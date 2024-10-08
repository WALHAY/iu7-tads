#include "../inc/regular_vector.h"

RegularVector *create_regular_vector(size_t length)
{
    printf("Create %zu len vector\n", length);
    RegularVector *result = malloc(sizeof(RegularVector));
    result->length = length;
    result->data = calloc(length, sizeof(int));
    return result;
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
