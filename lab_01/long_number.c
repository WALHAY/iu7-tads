#include "long_number.h"

void print_len_line(int offset, int len);

int read_long_number(char *ptr, long_number_t *new_number)
{
    char *new_line = strchr(ptr, '\n');
    if (new_line)
        *new_line = '\0';
    size_t len = strlen(ptr);

    char temp[len];
    strcpy(temp, ptr);

    // Check mantissa sign
    bool negative = *temp == '-';
    if (negative || *temp == '+')
    {
        move_str_left(temp, 1);
        len--;
    }

    // Find pointer index
    char *point_ptr = strchr(temp, '.');
    size_t point_index = len;
    if (point_ptr)
    {
        point_index = point_ptr - temp;
        move_str_left(point_ptr, 1);
        len--;
    }

    // Trim leading zeroes
    size_t diff = 0;
    while (temp[diff] == '0' && temp[diff + 1] != '\0')
        diff++;

    if (diff)
    {
        move_str_left(temp, diff);
        len -= diff;
        point_index -= diff;
    }
    // Leading zeroes remove

    size_t mantissa_end = len;
    char *exponent_ptr = strpbrk(temp, "eE");
    bool has_exponent = false;
    if (exponent_ptr)
    {
        has_exponent = true;
        mantissa_end = exponent_ptr - temp;
    }

    // Trim trailing zeroes
    while (mantissa_end - 1 >= point_index && temp[mantissa_end - 1] == '0')
        mantissa_end--;

    // Mantissa end found | Validation next
    if (mantissa_end == 0)
        return EMPTY_NUMBER_ERROR;

    if (mantissa_end >= MAX_MANTISSA_SIZE)
        return MANTISSA_OVERFLOW;

    for (size_t i = 0; i < mantissa_end; ++i)
        if (!isdigit(temp[i]))
            return WRONG_SYMBOL_ERROR;

    strncpy(new_number->mantissa, temp, mantissa_end);
    new_number->mantissa[mantissa_end] = '\0';
    new_number->sign = negative;
    new_number->point_pos = point_index;

    // Exponent start
    if (!has_exponent)
    {
        new_number->exponent = 0;
        return SUCCESS;
    }

    exponent_ptr++;
    bool exp_negative = *exponent_ptr == '-';
    if (exp_negative || *exponent_ptr == '+')
        exponent_ptr++;

    char *exp_start = exponent_ptr;
    while (*exp_start != '\0')
        if (!isdigit(*exp_start++))
            return WRONG_SYMBOL_ERROR;

    int exponent_value = (exp_negative ? -1 : 1) * atoi(exponent_ptr);
    if (exponent_value < -99999 || exponent_value > 99999)
        return EXPONENT_OVERFLOW;

    new_number->exponent = exponent_value;

    return SUCCESS;
}

void move_str_left(char *data, size_t offset)
{
    if (data == NULL)
        return;

    if (offset < 1)
        return;

    char temp[strlen(data)];
    strcpy(temp, data + offset);
    strcpy(data, temp);
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
        print_len_line(1, strlen(number->mantissa));
}
