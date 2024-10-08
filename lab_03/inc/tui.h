#pragma once

#include "comparison.h"
#include "defines.h"
#include "functions.h"
#include "regular_matrix.h"
#include "regular_vector.h"
#include "sparse_matrix.h"
#include "sparse_vector.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_operation(SparseMatrix **matrix, SparseVector **vector);

size_t input_enum(size_t max_options, char **options);

int input_value(char *title, bool min_limit, bool max_limit, int min_value, int max_value);

int input_matrix(SparseMatrix *matrix);

int input_vector(SparseVector *vector);

char *get_error_message(int error);
