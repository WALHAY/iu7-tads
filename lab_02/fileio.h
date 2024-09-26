#pragma once

#include "defines.h"
#include <stdio.h>

FILE *open_file(char *name, char *mode, int *rc);

void close_file(FILE *file);
