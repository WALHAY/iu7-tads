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
    char *options[] = {"Create new Matrix",
                       "Create new Vector",
                       "Input matrix",
                       "Input vector",
                       "Randomize matrix",
                       "Randomize vector",
                       "Multiply matrix on vector",
                       "Print matrix",
                       "Print vector",
                       "Compare",
                       "Exit"};
    size_t opt = input_enum(11, options);
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
        if (!vector)
            free(vector);

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
    case RANDOMIZE_MATRIX:
    {
        int fill_percent = input_value("matrix fill percent", true, true, 1, 100);
        generate_random_matrix(matrix, fill_percent / 100.0f);
        break;
    }
    break;
    case RANDOMIZE_VECTOR:
    {
        int fill_percent = input_value("vector fill percent", true, true, 1, 100);
        generate_random_vector(vector, fill_percent / 100.0f);
        break;
    }
    case MULTIPLICATION:
    {
        SparseMatrix *result = multiply_matrix_on_vector(matrix, vector);
        print_sparse_matrix(result);
        if (!result)
            free(result);
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

int input_value(char *title, bool min_limit, bool max_limit, int min_value, int max_value)
{
    int value = 0;
    printf("Enter %s: ", title);
    while (safe_int_input(&value) || (max_limit && value > max_value) || (min_limit && value < min_value))
        printf("Error: Wrong value!\n"
               "Enter %s again: ",
               title);
    return value;
}

void input_matrix(SparseMatrix *matrix)
{
    int element = 0;
    size_t row = 0;
    size_t column = 0;
    do
    {
        element = input_value("element value", false, false, 0, 0);
        row = input_value("element row", true, true, 0, matrix->rows);
        column = input_value("element column", true, true, 0, matrix->columns);
    } while (!add_matrix_element(matrix, element, row, column));
}

void input_vector(SparseVector *vector)
{
    int element = 0;
    size_t index = 0;
    do
    {
        element = input_value("element value", false, false, 0, 0);
        index = input_value("element index", true, true, 0, vector->length);
    } while (!add_vector_element(vector, element, index));
}

char *get_error_message(int error)
{
    switch (error)
    {
    default:
        return "Error: Error message not specified!";
    }
}
