#pragma once

#include "Defines.h"
#include "GraphvizIntegration.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeOperation(void);

size_t inputEnum(size_t max_options, char **options);

int inputValue(char *title, bool min_limit, bool max_limit, int min_value, int max_value);

char *inputString(char *title);
