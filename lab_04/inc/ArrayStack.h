#pragma once

#include "Defines.h"
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

#define LOAD_FACTOR 2
#define ARR_SIZE 20000

typedef struct
{
    uintptr_t *begin;
    uintptr_t *end;
    uintptr_t *stackPointer;
} ArrayStack;

ArrayStack *arrayStack(int *rc);

void destroyStackArr(ArrayStack *stack);

uintptr_t pushArr(ArrayStack *stack, uintptr_t ptr, int *rc);

uintptr_t popArr(ArrayStack *stack, int *rc);
