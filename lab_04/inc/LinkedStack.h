#pragma once

#include <stdlib.h>

typedef struct LinkedStackNode LinkedStackNode;

struct LinkedStackNode
{
    void *data;
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

LinkedStackNode *push(LinkedStack *stack);

LinkedStackNode *pop(LinkedStack *stack);
