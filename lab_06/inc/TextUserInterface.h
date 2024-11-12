#pragma once

#include "BinaryTree.h"
#include "Defines.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int executeOperation(TreeNode **head_ptr);

size_t inputEnum(size_t max_options, char **options);

float inputValue(char *title, bool min_limit, bool max_limit, float min_value, float max_value);

char *getErrorMessage(int rc);
