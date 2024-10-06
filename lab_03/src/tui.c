#include "../inc/tui.h"

static int safe_int_input(int *value)
{
    char temp[20];
    fgets(temp, 20, stdin);
    char *end = NULL;
    errno = 0;
    long val = strtol(temp, &end, 10);
    if (errno == ERANGE || errno == EINVAL)
        return NAN_ERROR;
    *value = val;
    return SUCCESS;
}

int execute_operation(SparseMatrix **mptr, SparseVector **vptr)
{
    SparseMatrix *matrix = *mptr;
    SparseVector *vector = *vptr;
    char *options[] = {
        "Create new Matrix", "Create new Vector", "Input matrix", "Input vector", "Multiply matrix on vector",
        "Print matrix",      "Print vector",      "Compare",      "Exit"};
    size_t opt = input_enum(9, options);
    printf("Processing: %s\n", *(options + opt));
    switch (opt)
    {
    case CREATE_MATRIX:
    {
        if (!matrix)
            free(matrix);

        size_t rows = input_value("matrix rows count", true, false, 1, 0);
        size_t columns = input_value("matrix columns count", true, false, 1, 0);
        *mptr = create_matrix(rows, columns, 0);
        break;
    }
    case CREATE_VECTOR:
    {
        size_t length = input_value("vector length", true, false, 1, 0);
        *vptr = create_vector(length, 0);
        break;
    }
    case INPUT_MATRIX:
        input_matrix(matrix);
        break;
    case INPUT_VECTOR:
        input_vector(vector);
        break;
    case MULTIPLICATION:
    {
        SparseMatrix *result = multiply_matrix_on_vector(matrix, vector);
        print_sparse_matrix(result);
        break;
    }
    case PRINT_MATRIX:
        print_sparse_matrix(matrix);
        break;
    case PRINT_VECTOR:
        print_sparse_vector(vector);
        break;
    case COMPARISON:
        break;
    case EXIT:
        exit(SUCCESS);
    }

    return SUCCESS;
}

size_t input_enum(size_t max_options, char **options)
{
    printf("\nPossible variants:\n");
    for (size_t i = 0; i < max_options; ++i)
        printf("\t%zu. %s\n", i, options[i]);

    size_t option = 0;
    printf("Option: ");
    while (safe_int_input((int *)&option) || option >= max_options)
        printf("Error: Wrong option!\n"
               "Enter option again: ");
    return option;
}

size_t input_value(char *title, bool min_limit, bool max_limit, int min_value, int max_value)
{
    int value = 0;
    printf("Enter %s: ", title);
    while (safe_int_input(&value) || (max_limit && value > max_value) || (min_limit && value < min_value))
        printf("Error: Wrong value!\nEnter %s again: ", title);
    return value;
}

void input_matrix(SparseMatrix *matrix)
{
    add_matrix_element(matrix, 1, 0, 0);
}

void input_vector(SparseVector *vector)
{
    add_vector_element(vector, 1, 0);
}

char *get_error_message(int error)
{
    switch (error)
    {
    default:
        return "Error: Error message not specified!";
    }
}
