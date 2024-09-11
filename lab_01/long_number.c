#include "long_number.h"

void print_len_line(int offset, int len);

int validate_mantissa(char *mantissa)
{
    size_t len = strlen(mantissa);
    for (size_t i = 0; i < len; ++i)
        if (!isdigit(mantissa[i]))
            return WRONG_SYMBOL_ERROR;
    return SUCCESS;
}

int validate_exponent(char *exponent)
{
    return SUCCESS;
}

int read_long_number(char *ptr, long_number_t *new_number)
{
    *strchr(ptr, '\n') = '\0';
    size_t len = strlen(ptr);
    char *point_ptr = strchr(ptr, '.');
    size_t point_index = len;
    if (point_ptr != NULL)
    {
        point_index = point_ptr - ptr;
        strcpy(point_ptr, point_ptr + 1);
    }

    // Trim left->right
    size_t diff = 0;
    while (ptr + diff < point_ptr && *(ptr + diff) == '0')
        diff++;

    if (diff > 0)
    {
        point_index -= diff;
        len -= diff;
        strcpy(ptr, ptr + diff);
    }

    // Trim right->left
    char *exponent_ptr = strpbrk(ptr, "eE");
    bool has_exponent = false;
    size_t exponent_index = len;
    if (exponent_ptr != NULL)
        exponent_index = exponent_ptr - ptr;
    else
        has_exponent = false;

    size_t mantissa_end = exponent_index - 1;

    while (mantissa_end >= 1 && mantissa_end - 1 >= point_index && *(ptr + mantissa_end - 1) == '0')
        mantissa_end--;

    if (mantissa_end != exponent_index)
    {
        if (has_exponent)
            strcpy(ptr + mantissa_end, exponent_ptr);
        else
            *(ptr + mantissa_end) = '\0';
    }

    // bool negative = *ptr == '-';
    // if (negative || *ptr == '+')
    // {
    //     strcpy(ptr, ptr + 1);
    // }

    // size_t mantissa_len = end - ptr;
    // if (mantissa_len > MAX_MANTISSA_SIZE)
    //     return MANTISSA_OVERFLOW;

    // start = ptr;
    // while (start < end)
    //     if (!isdigit(*start++))
    //         return WRONG_SYMBOL_ERROR;

    // Mantissa finished-Start exponent

    return SUCCESS;
}

void move_str_left(char *data, size_t offset)
{
    char buf[MAX_MANTISSA_SIZE + 1];
    strcpy(buf, data + offset);
    strcpy(data, buf);
}

void trim_mantissa(long_number_t *number)
{
    size_t ptr = 0;
    while (number->mantissa[ptr] == '0' && ptr < number->point_pos)
        ptr++;

    move_str_left(number->mantissa, ptr);

    int len = strlen(number->mantissa);
    while (len >= 0 && number->mantissa[--len] == '0')
        number->mantissa[len] = '\0';

    number->point_pos -= ptr;
}

void normalize(long_number_t *number)
{
    trim_mantissa(number);

    if (number->point_pos == 0)
    {
        size_t count = 0;
        while (number->mantissa[count] == '0')
            count++;
        if (count > 0)
        {
            move_str_left(number->mantissa, count);
            number->exponent -= count;
        }
    }
    else if (number->point_pos != 0)
    {
        number->exponent += number->point_pos;
        number->point_pos = 0;
    }
}

bool is_less_divider(char *dividend, char *divider, size_t pos)
{
    for (size_t i = 0; i < pos; ++i)
        if (dividend[i] > '0')
            return true;

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

void create_bigger_mantissa(char *mantissa, char *new_mantissa, size_t size)
{
    int len = strlen(mantissa);
    strncpy(new_mantissa, mantissa, len);
    for (int i = len; i < size; ++i)
        new_mantissa[i] = '0';
    new_mantissa[size - 1] = '\0';
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

    char new_mantissa[MAX_MANTISSA_SIZE * 2 + 1];
    create_bigger_mantissa(dividend->mantissa, new_mantissa, MAX_MANTISSA_SIZE * 2);

    size_t ptr = 0;
    while (ptr < MAX_MANTISSA_SIZE)
    {
        if (is_less_divider(new_mantissa, divider->mantissa, ptr))
        {
            subtract_divider(new_mantissa, divider->mantissa, ptr);
            result[ptr]++;
        }
        else
            ptr++;
    }

    strcpy(dividend->mantissa, result);
    dividend->mantissa[MAX_MANTISSA_SIZE] = '\0';
    dividend->exponent -= divider->exponent - 1;
    dividend->sign ^= divider->sign;
    normalize(dividend);
    return SUCCESS;
}

void print_long_number(long_number_t *number, bool print_size)
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

    if (print_size)
        print_len_line(2, strlen(number->mantissa));
}
