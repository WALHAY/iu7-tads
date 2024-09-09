#include "long_number.h"

void move_mantissa_left(int *mantissa, size_t offset);

int read_long_number(char *ptr, long_number_t *new_number)
{
    size_t mantissa_ptr = 0;
    size_t point_counter = 0;
    size_t sign_counter = 0;
    for (; *ptr != '\0' && *ptr != '\n'; ++ptr)
    {
        if (mantissa_ptr >= MAX_MANTISSA_SIZE)
            return MANTISSA_OVERFLOW;

        if (isdigit(*ptr))
            new_number->mantissa[mantissa_ptr++] = *ptr;
        else if (*ptr == '+' || *ptr == '-')
        {
            if (*ptr == '-')
                new_number->sign = true;
            if (sign_counter++)
                return MANTISSA_SIGN_COUNT_ERROR;
        }
        else if (*ptr == '.')
        {
            if (point_counter++)
                return POINT_COUNT_ERROR;

            new_number->point_pos = mantissa_ptr;
        }
        else if (*ptr == 'E' || *ptr == 'e')
        {
            ptr++;
            break;
        }
        else
            return WRONG_SYMBOL_ERROR;
    }

    int exponent = 0;
    sign_counter = 0;
    bool exponent_sign = false;
    for (; *ptr != '\0' && *ptr != '\n'; ++ptr)
    {
        if (isdigit(*ptr))
            exponent = exponent * 10 + (*ptr - '0');
        else if (*ptr == '+' || *ptr == '-')
        {
            if (*ptr == '-')
                exponent_sign = true;
            if (sign_counter++)
                return EXPONENT_SIGN_COUNT_ERROR;
        }
        else
            return WRONG_SYMBOL_ERROR;
    }
    new_number->exponent = exponent * (exponent_sign ? -1 : 1);
    return SUCCESS;
}

void move_str_left(char *data, size_t offset)
{
    strcpy(data, data + offset);
}

void trim_mantissa(long_number_t *number)
{
    size_t ptr = 0;
    while (number->mantissa[ptr] == '0' && ptr < number->point_pos)
        ptr++;

    size_t len = strlen(number->mantissa);
    while (len >= 0 && number->mantissa[--len] == '0')
        number->mantissa[len] = '\0';

    move_str_left(number->mantissa, ptr);
    number->point_pos -= ptr;
}

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
        number->exponent += number->point_pos;
        number->point_pos = 0;
    }
    return 0;
}

bool is_less_divider(char *dividend, char *divider, size_t pos)
{
    for (size_t i = 0; i < pos; ++i)
    {
        if (dividend[i] > '0')
            return true;
    }

    size_t divider_len = strlen(divider);
    for (size_t i = 0; i < divider_len; ++i)
    {
        if (dividend[pos + i] > divider[i])
            return true;
        if (dividend[pos + i] < divider[i])
            return false;
    }

    return true;
}

void subtract_divider(char *dividend, char *divider, size_t pos)
{
    size_t divider_len = strlen(divider);
    bool take_next = false;
    for (int i = pos + divider_len - 1; i >= 0; --i)
    {
        int current = dividend[i] - (i >= pos ? divider[i - pos] : '0') - take_next;

        take_next = false;
        if (current < 0)
        {
            current += 10;
            take_next = true;
        }
        dividend[i] = current + '0';
    }
}

void apply_zeroes(long_number_t *number)
{
    for (size_t i = strlen(number->mantissa); i < MAX_MANTISSA_SIZE; ++i)
        number->mantissa[i] = '0';
    number->mantissa[MAX_MANTISSA_SIZE] = '\0';
}

bool is_zero(char *number)
{
    return strpbrk(number, "123456789") == NULL;
}

int divide(long_number_t *dividend, long_number_t *divider)
{
    if (is_zero(divider->mantissa))
        return ZERO_DIVISION;

    char result[MAX_MANTISSA_SIZE + 1];
    for (size_t i = 0; i < MAX_MANTISSA_SIZE; ++i)
        result[i] = '0';
    result[MAX_MANTISSA_SIZE] = '\0';

    apply_zeroes(dividend);

    size_t ptr = 0;
    size_t max_mantissa = MAX_MANTISSA_SIZE - strlen(divider->mantissa) + 1;
    while (ptr <= max_mantissa)
    {
        if (is_less_divider(dividend->mantissa, divider->mantissa, ptr))
        {
            subtract_divider(dividend->mantissa, divider->mantissa, ptr);
            result[ptr]++;
        }
        else
            ptr++;
    }

    strcpy(dividend->mantissa, result);
    dividend->exponent -= divider->exponent;
    dividend->sign ^= divider->sign;
    normalize(dividend);
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

    printf("e%d\n", number->exponent);
}
