#include "../inc/tui.h"

static int safe_int_input(int *value)
{
    char temp[20];
    fgets(temp, 20, stdin);
    char *end = NULL;
    errno = 0;
    long val = strtol(temp, &end, 10);
    if (errno == ERANGE || errno == EINVAL || end == temp)
        return NAN_ERROR;
    *value = val;
    return SUCCESS;
}

static void overwrite_matrix_add(SparseMatrix *matrix, int value, size_t row, size_t column)
{
    static char *opts[] = {"No", "Yes"};
    if (add_matrix_element(matrix, value, row, column) == ELEMENT_EXIST_ERROR)
    {
        printf("Element exist in matrix, do you want to overwrite it?");
        size_t opt = input_enum(2, opts);
        if (opt)
            replace_matrix_element(matrix, value, row, column);
    }
}

static void overwrite_vector_add(SparseVector *matrix, int value, size_t index)
{
    static char *opts[] = {"No", "Yes"};
    if (add_vector_element(matrix, value, index) == ELEMENT_EXIST_ERROR)
    {
        printf("Element exist in vector, do you want to overwrite it?");
        size_t opt = input_enum(2, opts);
        if (opt)
            replace_vector_element(matrix, value, index);
    }
}

static void input_matrix_full(SparseMatrix *matrix)
{
    for (size_t row = 0; row < matrix->rows; ++row)
    {
        for (size_t column = 0; column < matrix->columns; ++column)
        {
            char title[120];
            sprintf(title, "value of element in %zu row %zu column", row, column);
            int value = input_value(title, false, false, 0, 0);
            overwrite_matrix_add(matrix, value, row, column);
        }
    }
}

static void input_matrix_positional(SparseMatrix *matrix)
{
    size_t size = input_value("count of elements you want to input", true, true, 0, matrix->rows * matrix->columns);
    for (size_t i = 0; i < size; ++i)
    {
        int value = input_value("element value", false, false, 0, 0);
        size_t row = input_value("element row", true, true, 0, matrix->rows - 1);
        size_t column = input_value("element column", true, true, 0, matrix->columns - 1);
        overwrite_matrix_add(matrix, value, row, column);
        printf("\n");
    }
}

static void input_vector_full(SparseVector *vector)
{
    for (size_t i = 0; i < vector->length; ++i)
    {
        char title[120];
        sprintf(title, "%zu element value", i);
        int value = input_value(title, false, false, 0, 0);
        overwrite_vector_add(vector, value, i);
    }
}

static void input_vector_positional(SparseVector *vector)
{
    size_t size = input_value("count of elements you want to input", true, true, 0, vector->length);
    for (size_t i = 0; i < size; ++i)
    {
        int value = input_value("element value", false, false, 0, 0);
        size_t index = input_value("element index", true, true, 0, vector->length - 1);
        overwrite_vector_add(vector, value, index);
        printf("\n");
    }
}

static void collect_statistics(void)
{
    char *opts[] = {"Algorithm time comparison", "Algorithm memory comparison", "Vector memory comparison",
                    "Matrix vector compariosn"};
    size_t opt = input_enum(4, opts);
    switch (opt)
    {
    case 0:
        multiplication_time_comparison();
        break;
    case 1:
        multiplication_memory_comparison();
        break;
    case 2:
        vector_memory_comparsion();
        break;
    case 3:
        matrix_memory_comparsion();
        break;
    }
}

int execute_operation(SparseMatrix **mptr, SparseVector **vptr)
{
    SparseMatrix *matrix = *mptr;
    SparseVector *vector = *vptr;
    static char *options[] = {"Create new Matrix",
                              "Recreate Vector",
                              "Input matrix",
                              "Input vector",
                              "Randomize matrix",
                              "Randomize vector",
                              "Multiply vector by matrix (sparse)",
                              "Multiply vector by matrix (basic)",
                              "Print matrix",
                              "Print vector",
                              "Compare TaDS",
                              "Exit"};
    size_t opt = input_enum(12, options);
    printf("Processing: %s\n", *(options + opt));
    switch (opt)
    {
    case CREATE_MATRIX:
    {
        free_matrix(matrix);

        size_t rows = input_value("matrix rows count", true, false, 1, 0);
        size_t columns = input_value("matrix columns count", true, false, 1, 0);
        *mptr = create_matrix(rows, columns, 0);
        printf("Created matrix of size rows: %zu - columns: %zu\n", rows, columns);

        free_vector(vector);

        *vptr = create_vector(rows, 0);
        printf("Created vector of length %zu\n", rows);
        break;
    }
    case CREATE_VECTOR:
    {
        if (!matrix)
        {
            printf("Specify matrix first\n");
            break;
        }

        free_vector(vector);

        size_t length = 0;
        if (matrix)
            length = matrix->rows;
        *vptr = create_vector(length, 0);
        printf("Created vector of length %zu\n", length);
        break;
    }
    case INPUT_MATRIX:
        return input_matrix(matrix);
    case INPUT_VECTOR:
        return input_vector(vector);
    case RANDOMIZE_MATRIX:
    {
        int fill_percent = input_value("matrix fill percent", true, true, 1, 100);
        return generate_random_matrix(matrix, fill_percent / 100.0f);
    }
    case RANDOMIZE_VECTOR:
    {
        int fill_percent = input_value("vector fill percent", true, true, 1, 100);
        return generate_random_vector(vector, fill_percent / 100.0f);
    }
    case MULTIPLICATION_SPARSE:
    {
        SparseVector *result = create_vector(vector->length, vector->length);
        multiply_vector_by_matrix(vector, matrix, result);
        fit_to_size(result);
        printf("\nMultiplication result:\n");
        print_sparse_vector(result);
        free_vector(result);
        break;
    }
    case MULTIPLICATION_REGULAR:
    {
        RegularVector *rvector = from_sparse_to_regular_vector(vector);
        RegularMatrix *rmatrix = from_sparse_to_regular_matrix(matrix);
        RegularVector *rresult = create_regular_vector(rvector->length);
        multiply_vector_by_matrix_basic(rvector, rmatrix, rresult);
        printf("\nMultiplication result:\n");
        SparseVector *sresult = from_regular_to_sparse_vector(rresult);
        print_sparse_vector(sresult);
        free_regular_vector(rvector);
        free_regular_matrix(rmatrix);
        free_regular_vector(rresult);
        free_vector(sresult);
        break;
    }
    case PRINT_MATRIX:
        return print_sparse_matrix(matrix);
    case PRINT_VECTOR:
        return print_sparse_vector(vector);
    case COMPARISON:
        collect_statistics();
        break;
    case EXIT:
        free_vector(vector);
        free_matrix(matrix);
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

int input_matrix(SparseMatrix *matrix)
{
    if (!matrix)
        return NULLPTR_ERROR;

    if (matrix->rows < MAX_FULL_MATRIX_INPUT_LEN && matrix->columns < MAX_FULL_MATRIX_INPUT_LEN)
    {
        static char *opts[] = {"Input full matrix", "Input elements by position"};
        size_t option = input_enum(2, opts);
        if (option)
            input_matrix_positional(matrix);
        else
            input_matrix_full(matrix);
    }
    else
        input_matrix_positional(matrix);
    return SUCCESS;
}

int input_vector(SparseVector *vector)
{
    if (!vector)
        return NULLPTR_ERROR;

    if (vector->length < MAX_FULL_VECTOR_INPUT_LEN)
    {
        static char *opts[] = {"Input full vector", "Input elements by position"};
        size_t option = input_enum(2, opts);
        if (option)
            input_vector_positional(vector);
        else
            input_vector_full(vector);
    }
    else
        input_vector_positional(vector);
    return SUCCESS;
}

char *get_error_message(int error)
{
    switch (error)
    {
    case SUCCESS:
        return "Everything is fine!";
        break;
    case WRONG_POS_ERROR:
        return "Error: Wrong position of element specified!";
    case NULLPTR_ERROR:
        return "Error: Null pointer passed to function!";
    case ALLOC_ERROR:
        return "Error: Failed to allocate memory!";
    case ELEMENT_EXIST_ERROR:
        return "Error: Element is already exist in structure!";
    case NAN_ERROR:
        return "Error: Not a number!";
    case REPLACE_ERROR:
        return "Error: Failed to replace exisiting element!";
    default:
        return "Error: Error message not specified!";
    }
}
