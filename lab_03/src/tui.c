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

void print_rules(void)
{
}

void print_limitations(void)
{
}

int execute_operation()
{
    char *options[] = {
        "Input matrix",
        "Input vector",
        "Multiply matrix on vector"
    };
    size_t opt = input_enum(3, options);
    printf("Processing: %s\n", *(options + opt));
    switch (opt)
    {
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

char *get_error_message(int error)
{
    switch(error)
    {
        default:
        return "Error: Error message not specified!";
    }
}
