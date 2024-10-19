#pragma once

#include "Defines.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct LinkedStackNode LinkedStackNode;

struct LinkedStackNode
{
    uintptr_t data;
    LinkedStackNode *next;
};

typedef struct
{
    LinkedStackNode *stackPointer;
} LinkedStack;

LinkedStack *linkedStack(int *rc);

void destroyStack(LinkedStack *stack);

LinkedStackNode *linkedStackNode(int *rc);

void destroyNode(LinkedStackNode *node);

uintptr_t push(LinkedStack *stack, int *rc);

uintptr_t pop(LinkedStack *stack, int *rc);
