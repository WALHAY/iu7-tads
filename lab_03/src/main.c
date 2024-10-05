#include "../inc/sparse_matrix.h"

int main(void)
{
    SparseMatrix *mx = create_matrix(4, 4, 5);
    add_matrix_element(mx, 1, 1, 2);
    add_matrix_element(mx, 2, 1, 1);
    print_sparse_matrix(mx);

    return 0;
}
