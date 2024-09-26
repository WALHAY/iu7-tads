#pragma once

#include "defines.h"
#include "table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_rules(void);

void execute_operation(Table *table);

int validate_input(char *field, char *title, size_t max_size);

int input_enum(size_t *option, size_t max_options, char **options);

int input_value(size_t *value, char *title, bool has_range, size_t max_value);
