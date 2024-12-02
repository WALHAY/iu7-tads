#pragma once

#include "AVLTree.h"
#include "BinaryTree.h"
#include "Comparison.h"
#include "Defines.h"
#include "GraphvizIntegration.h"
#include "HashMap.h"
#include "LinkedHashMap.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int executeOperation();

size_t inputEnum(size_t max_options, char **options);

int inputValue(char *title, bool min_limit, bool max_limit, int min_value, int max_value);

char *inputString(char *title);

char *getErrorMessage(int rc);
