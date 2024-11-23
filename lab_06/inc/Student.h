#pragma once

#include "Defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    float score;
} StudentData;

StudentData *createData(char *name, float score, int *rc);

void printStudent(StudentData *data);

void freeData(StudentData *data);
