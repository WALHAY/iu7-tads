#include "../inc/functions.h"
#include "../inc/sparse_matrix.h"
#include "../inc/sparse_vector.h"

int main(void)
{
    printf("Matrix:\n");
    SparseMatrix *mx = create_matrix(4, 4, 8);
    generate_random_matrix(mx, 8);
    print_sparse_matrix(mx);

    printf("Vector:\n");
    SparseVector *v = create_vector(10);
    add_vector_element(v, 4, 0);
    add_vector_element(v, 3, 1);
    add_vector_element(v, 2, 2);
    add_vector_element(v, 1, 3);
    print_sparse_vector(v);

    SparseMatrix *result = multiply_matrix_on_vector(mx, v);
    printf("Result:\n");
    print_sparse_matrix(result);
    return 0;
}
