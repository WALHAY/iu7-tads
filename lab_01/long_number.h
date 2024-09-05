#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    bool mantissa_sign;
    char *mantissa;
    bool order_sign;
    long long order;
} long_number_t;

/*
 * Деление уголком(пример)
 *  65142 | 423
 * -423   |----
 *  ___    154
 *  2284
 * -2115
 *  ____
 *   1692
 *  -1692
 *   ____
 *      0
 */

int divide(long_number_t *dividend, long_number_t *divider, long_number_t **result);

void print_long_number(long_number_t *number);
