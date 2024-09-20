#include "utils.h"

void print_rules()
{
    printf("Программа деления двух вещественных чисел\n");
    printf("Максимально разрешенная длина мантиссы каждого числа - 40 символов\n");
    printf("Максимально разрешенная длина экспоненты каждого числа - 5 символов\n");
    printf("Число может быть записано как в обычной форме, так и в экспоненциальной\n\n");
}

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

    for (size_t i = 0; i <= len; ++i)
        if (i % 5 == 0)
            printf("|");
        else
            printf("-");

    printf("\n");

    for (size_t i = 0; i < offset; ++i)
        printf(" ");

    for (size_t i = 0; i <= len; i += 5)
        printf("%zu%s", i, i < 10 ? "    " : "   ");
}

void print_input_len_line(int offset, int len)
{
    for (size_t i = 0; i < offset; ++i)
        printf(" ");

    for (size_t i = 0; i <= len; i += 5)
        printf("%zu%s", i, i < 10 ? "    " : "   ");

    printf("\n");

    for (size_t i = 0; i < offset; ++i)
        printf(" ");

    for (size_t i = 0; i <= len; ++i)
        if (i % 5 == 0)
            printf("|");
        else
            printf("-");
    printf("\n");
}

void print_err(int rc)
{
    switch (rc)
    {
    case SUCCESS:
        printf("Error: everything is fine!");
        break;
    case IO_ERR:
        printf("Error: IO Failed!");
        break;
    case MANTISSA_OVERFLOW:
        printf("Error: mantissa is bigger than %d symbols!", MAX_MANTISSA_SIZE);
        break;
    case EXPONENT_OVERFLOW:
        printf("Error: exponent is bigger than 5 symbols!");
        break;
    case EMPTY_NUMBER_ERROR:
        printf("Error: empty number!");
        break;
    case WRONG_SYMBOL_ERROR:
        printf("Error: entered wrong symbol in number!");
        break;
    case ZERO_DIVISION:
        printf("Error: zero division!");
        break;
    case NORMALIZATION_ERROR:
        printf("Error: normalization failed!");
        break;
    }
    printf("\n");
}
