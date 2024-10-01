#pragma once

#include "comparison.h"
#include "defines.h"
#include "fileio.h"
#include "table.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_rules(void);

void print_limitations(void);

int execute_operation(Table *table);

void input_string(char *field, char *title, size_t max_size);

size_t input_enum(size_t max_options, char **options);

size_t input_value(char *title, bool min_limit, bool max_limit, int min_value, int max_value);

char *get_error_message(int error);
