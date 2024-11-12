#pragma once

#include "Defines.h"
#include <stdlib.h>

typedef struct
{
    const char *name;
    float score;
} StudentData;

StudentData *createData(const char *name, float score, int *rc);

void freeData(StudentData *data);
