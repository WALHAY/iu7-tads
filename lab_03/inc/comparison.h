#pragma once

#define _GNU_SOURCE

#include "functions.h"
#include "regular_matrix.h"
#include "regular_vector.h"
#include "sparse_matrix.h"
#include "sparse_vector.h"
#include <stdlib.h>
#include <time.h>

void compare_multiplication_time(size_t rows, size_t columns, float fill);

void compare_matrix_memory(size_t rows, size_t columns, float fill);

void compare_vector_memory(size_t length, float fill);

void compare_tads(void);
