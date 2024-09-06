#pragma once

#include "defines.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    bool sign;
    char mantissa[MAX_MANTISSA_SIZE + 1];
    int order;
    size_t point_pos;
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

int read_long_number(char *number, long_number_t *new_number);

void trim_mantissa(long_number_t *number);

int normalize(long_number_t *number);

bool is_less_mantissa(long_number_t *first, long_number_t *second);

int subtract_mantissa(long_number_t *first, long_number_t *second);

int divide(long_number_t *dividend, long_number_t *divider, long_number_t *result);

void print_long_number(long_number_t *number);
