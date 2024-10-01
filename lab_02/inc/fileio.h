#pragma once

#include "../inc/table.h"
#include "defines.h"
#include <stdio.h>
#include <string.h>

FILE *open_file(char *name, char *mode, int *rc);

void close_file(FILE *file);
