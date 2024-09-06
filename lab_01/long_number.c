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
 * Negative - left, positive - right
 */
void move_str_left(char *str, size_t offset)
{
    char buf[MAX_MANTISSA_SIZE];
    strcpy(buf, str + offset);
    strcpy(str, buf);
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

    move_str_left(number->mantissa, -ptr);
    number->point_pos -= ptr;
}

/*
 * 00503e10 -> 0.503e12
 */
int normalize(long_number_t *number)
{
    trim_mantissa(number);

    if (number->point_pos == 0)
    {
        size_t count = 0;
        while (number->mantissa[count] == '0')
            count++;
        if (count > 0)
            move_str_left(number->mantissa, count);
        return count;
    }
    else if (number->point_pos != 0)
    {
        number->order += number->point_pos;
        number->point_pos = 0;
    }
    return 0;
}

bool is_less_mantissa(long_number_t *first, long_number_t *second)
{
    return strcmp(first->mantissa, second->mantissa) <= 0;
}

/*
 * first mantissa should be bigger than second
 */
int subtract_mantissa(long_number_t *first, long_number_t *second)
{
    int len = strlen(second->mantissa);

    bool subtract_next = false;
    for (int i = len - 1; i >= 0; --i)
    {
        int current = first->mantissa[i] - second->mantissa[i] - subtract_next;
        subtract_next = false;
        if (current < 0)
        {
            subtract_next = true;
            current += 10;
        }
        first->mantissa[i] = '0' + current;
    }

    return SUCCESS;
}

int divide(long_number_t *dividend, long_number_t *divider, long_number_t *result)
{
    char new_mantissa[MAX_MANTISSA_SIZE + 1];
    for (size_t i = 0; i < MAX_MANTISSA_SIZE; ++i)
        new_mantissa[i] = '0';
    new_mantissa[MAX_MANTISSA_SIZE] = '\0';

    size_t ptr = 0;
    while (ptr < MAX_MANTISSA_SIZE && is_less_mantissa(divider, dividend))
    {
        subtract_mantissa(dividend, divider);
        new_mantissa[ptr]++;
#ifdef DEBUG
        printf("Division step: ");
        print_long_number(dividend);
        printf("Current mantissa pointer: %zu\n", ptr);
#endif
        ptr += normalize(dividend);
    }
    strcpy(dividend->mantissa, new_mantissa);
    return SUCCESS;
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
