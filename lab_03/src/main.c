#include "../inc/functions.h"
#include "../inc/sparse_matrix.h"
#include "../inc/sparse_vector.h"

int main(void)
{
    printf("Matrix:\n");
    SparseMatrix *mx = create_matrix(30, 30, 2);
    add_matrix_element(mx, 1, 0, 0);
    add_matrix_element(mx, 1, 29, 29);
    print_sparse_matrix(mx);

    printf("Vector:\n");
    SparseVector *v = create_vector(30, 2);
    add_vector_element(v, 1, 0);
    add_vector_element(v, 1, 29);
    print_sparse_vector(v);

    printf("Result:\n");
    SparseMatrix *result = multiply_matrix_on_vector(mx, v);
    print_sparse_matrix(result);
    return 0;
}
