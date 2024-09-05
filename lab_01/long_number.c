#include "long_number.h"

int read_long_number(char *ptr, long_number_t *new_number)
{
    size_t mantissa_ptr = 0;
    size_t point_counter = 0;
    for (; *ptr != '\0'; ++ptr)
    {
        if (isdigit(*ptr))
            new_number->mantissa[mantissa_ptr++] = *ptr;
        else if (*ptr == '.')
        {
            if (point_counter++)
                return DOUBLE_POINT_ERROR;

            new_number->point_pos = mantissa_ptr;
        }
        else if (*ptr == 'E' || *ptr == 'e')
        {
            ptr++;
            break;
        }
    }

#ifdef DEBUG
    printf("Mantissa read: %s\n", new_number->mantissa);
    printf("Point position: %zu\n", new_number->point_pos);
#endif

    int order = 0;
    for (; *ptr != '\0'; ++ptr)
    {
        if (isdigit(*ptr))
            order = order * 10 + (*ptr - '0');
        else
            return INVALID_FORMAT_ERROR;
    }
#ifdef DEBUG
    printf("Order read: %d\n", order);
#endif
    new_number->order = order;
    return SUCCESS;
}

/*
 * 00005.10 -> 5.10
 * 0005e10 -> 5e10
 */
void trim_mantissa(long_number_t *number)
{
    size_t ptr = 0;
    while (number->mantissa[ptr] == '0' && ptr < number->point_pos)
        ++ptr;

#ifdef DEBUG
    printf("Mantissa trimmed: %zu zeroes will be deleted!\n", ptr);
#endif

    char temp[MAX_MANTISSA_SIZE + 1];
    strcpy(temp, number->mantissa + ptr);
    strcpy(number->mantissa, temp);
    number->point_pos -= ptr;
}

/*
 * 00503e10 -> 0.503e12
 */
int normalize(long_number_t *number)
{
    trim_mantissa(number);
}

int subtract(long_number_t *first, long_number_t *second)
{
}

int divide(long_number_t *dividend, long_number_t *divider, long_number_t **result)
{
}

void print_long_number(long_number_t *number)
{
    if (number->sign)
        printf("-");

    if (number->point_pos == 0)
        printf("0");

    size_t i = 0;
    for (; i < number->point_pos; ++i)
        printf("%c", number->mantissa[i]);

    printf(".");

    for (; number->mantissa[i] != '\0'; ++i)
        printf("%c", number->mantissa[i]);

    printf("e%d\n", number->order);
}
