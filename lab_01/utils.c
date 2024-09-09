#include "utils.h"

int read_number_wrapper(long_number_t *number)
{
    char *number_str = NULL;
    size_t size = 0;
    getline(&number_str, &size, stdin);
    if (number_str == NULL)
        return IO_ERR;

    return read_long_number(number_str, number);
}

void print_err(int rc)
{
    switch (rc)
    {
    case SUCCESS:
        printf("Error: Everything is fine!");
        break;
    case NULLPTR_ERROR:
        printf("Error: Nullpointer used!");
        break;
    case ZERO_DIVISION:
        printf("Error: Trying to divide on zero!");
        break;
    case MANTISSA_OVERFLOW:
        printf("Error: Mantissa is bigger than %d symbols!", MAX_MANTISSA_SIZE);
        break;
    }
}
