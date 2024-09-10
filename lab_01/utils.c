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

void print_len_line(int offset, int len)
{
    for (size_t i = 0; i < offset; ++i)
        printf(" ");

    for (size_t i = 0; i < len; ++i)
        if (i % 5 == 0)
            printf("|");
        else
            printf("-");

    printf("\n");

    for (size_t i = 0; i < offset; ++i)
        printf(" ");

    for (size_t i = 0; i < len; i += 5)
        printf("%zu%s", i + 1, i < 10 ? "    " : "   ");
}

void print_err(int rc)
{
    switch (rc)
    {
    case SUCCESS:
        printf("Error: Everything is fine!");
        break;
    case ZERO_DIVISION:
        printf("Error: Trying to divide on zero!");
        break;
    case MANTISSA_OVERFLOW:
        printf("Error: Mantissa is bigger than %d symbols!", MAX_MANTISSA_SIZE);
        break;
    case IO_ERR:
        printf("Error: IO Failed!");
        break;
    case MANTISSA_SIGN_COUNT_ERROR:
        printf("Error: more than 1 sign symbol in mantissa!");
        break;
    case EXPONENT_SIGN_COUNT_ERROR:
        printf("Error: more than 1 sign symbol in exponent!");
        break;
    case POINT_COUNT_ERROR:
        printf("Error: more than 1 point in mantissa!");
        break;
    case WRONG_SYMBOL_ERROR:
        printf("Error: entered wrong symbol in number!");
        break;
    case EMPTY_NUMBER_ERROR:
        printf("Error: empty number!");
        break;
    }
    printf("\n");
}
