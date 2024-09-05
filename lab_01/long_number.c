#include "long_number.h"

int divide(long_number_t *dividend, long_number_t *divider, long_number_t **result)
{
    // *result = malloc(sizeof(long_number_t));
    // if (*result == NULL)
    //     return 1;

    return 0;
}

void print_long_number(long_number_t *number)
{
    char *last_zero = strrchr(number->mantissa, '0');
    if (last_zero)
        *(last_zero + 1) = '\0';
    printf("%c0.%sE%c%lld", (number->mantissa_sign ? '-' : '\0'), number->mantissa, (number->order_sign ? '-' : '\0'),
           number->order);
}
