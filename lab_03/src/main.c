#include "../inc/sparse_matrix.h"
#include "../inc/sparse_vector.h"
#include "../inc/tui.h"
#include <stdbool.h>

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc == 2 && !strcmp(argv[1], "comparison_only"))
    {
        FILE *file = fopen("collected_data.txt", "w");
        if (file)
        {
            collect_all_data_to_file(file);
            fclose(file);
        }
        return 0;
    }
    SparseMatrix *matrix = create_matrix(3, 3, 0);
    SparseVector *vector = create_vector(3, 0);

    while (true)
        execute_operation(&matrix, &vector);
    return 0;
}
