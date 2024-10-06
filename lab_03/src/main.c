#include "../inc/sparse_matrix.h"
#include "../inc/sparse_vector.h"
#include "../inc/tui.h"
#include <stdbool.h>

int main(void)
{
    SparseMatrix *matrix = create_matrix(30, 30, 0);
    SparseVector *vector = create_vector(30, 0);

    while (true)
        execute_operation(&matrix, &vector);
    return 0;
}
