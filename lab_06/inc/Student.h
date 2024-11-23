#pragma once

#include "Defines.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    float score;
} StudentData;

int surnameComparator(const StudentData *first, const StudentData *second);

int scoreComparator(const StudentData *first, const StudentData *second);

bool scoreFilter(const StudentData *first);

StudentData *createData(char *name, float score, int *rc);

void printStudent(StudentData *data);

void freeData(StudentData *data);
