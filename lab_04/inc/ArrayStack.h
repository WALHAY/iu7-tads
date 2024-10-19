#pragma once

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

#define LOAD_FACTOR 2

typedef struct
{
    uintptr_t *begin;
    uintptr_t *end;
    uintptr_t *stackPointer;
} ArrayStack;

ArrayStack *arrayStack(size_t init_size);

uintptr_t push_arr(ArrayStack *stack, uintptr_t ptr);

uintptr_t pop_arr(ArrayStack *stack);
