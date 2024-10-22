#pragma once

#include "Defines.h"
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

#define LOAD_FACTOR 2
#define INITIAL_SIZE 8

typedef struct
{
    uintptr_t *begin;
    uintptr_t *end;
    uintptr_t *stackPointer;
} ArrayStack;

ArrayStack *arrayStack(size_t init_size, int *rc);

void destroyStackArr(ArrayStack *stack);

uintptr_t pushArr(ArrayStack *stack, uintptr_t ptr, int *rc);

uintptr_t popArr(ArrayStack *stack, int *rc);
