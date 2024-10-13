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

void multiplication_time_comparison(void);

void multiplication_memory_comparison(void);

void matrix_memory_comparsion(void);

void vector_memory_comparsion(void);

void collect_all_data_to_file(FILE *file);
