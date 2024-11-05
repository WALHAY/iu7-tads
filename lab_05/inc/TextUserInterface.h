#pragma once

#include "Comparison.h"
#include "Defines.h"
#include "Statistic.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int executeOperation(void);

size_t inputEnum(size_t max_options, char **options);

float inputValue(char *title, bool min_limit, bool max_limit, float min_value, float max_value);

void inputTimeSpecification(TimeSpecification *timings);

void printCurrentTimings(void);

char *getErrorMessage(int rc);
