#include "../inc/sparse_matrix.h"
#include "../inc/sparse_vector.h"
#include "../inc/tui.h"
#include <stdbool.h>

int main(void)
{
    SparseMatrix *matrix = NULL;
    SparseVector *vector = NULL;

    while (true)
        execute_operation(&matrix, &vector);
    return 0;
}
