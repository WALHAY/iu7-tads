#pragma once

#include "defines.h"
#include "long_number.h"
#include <stdio.h>
#include <stdlib.h>

int read_number_wrapper(long_number_t *number);

void print_len_line(int offset, int len);

void print_err(int rc);
