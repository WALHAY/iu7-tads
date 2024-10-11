#pragma once

#define _GNU_SOURCE

#include "functions.h"
#include "regular_matrix.h"
#include "regular_vector.h"
#include "sparse_matrix.h"
#include "sparse_vector.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRY 50
#define MAX_OUT_TIME_WIDTH 10
#define MAX_OUT_ELEMENT_WIDTH 8

void compare_multiplication_time(size_t rows, size_t columns, float fill);

void compare_matrix_memory(size_t rows, size_t columns, float fill);

void compare_vector_memory(size_t length, float fill);

void multiplication_time_comparison(void);

void matrix_memory_comparsion(void);

void vector_memory_comparsion(void);
