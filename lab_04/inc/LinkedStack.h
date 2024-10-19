#pragma once

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

LinkedStack *linkedStack();

void destroyStack(LinkedStack *stack);

LinkedStackNode *linkedStackNode();

void destroyNode(LinkedStackNode *node);

uintptr_t push(LinkedStack *stack);

uintptr_t pop(LinkedStack *stack);
