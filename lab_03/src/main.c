#include "../inc/sparse_matrix.h"

int main(void)
{
    SparseMatrix *mx = create_matrix(25, 25, 300);
    generate_random_matrix(mx, 50);
    print_sparse_matrix(mx);

    return 0;
}
