#include "LinkedStack.h"

#define MAX_FREED 100000

uintptr_t freedMemory[MAX_FREED];
size_t freedIndex = 0;

LinkedStack *linkedStack(int *rc)
{
    LinkedStack *stack = malloc(sizeof(LinkedStack));
    if (stack)
    {
        stack->stackPointer = NULL;
        return stack;
    }
    *rc = ALLOC_ERROR;
    return NULL;
}

void destroyStack(LinkedStack *stack)
{
    LinkedStackNode *node = stack->stackPointer;
    while (node)
    {
        LinkedStackNode *next = node->next;
        destroyNode(node);
        node = next;
    }
    free(stack);
}

LinkedStackNode *linkedStackNode(int *rc)
{
    LinkedStackNode *node = malloc(sizeof(LinkedStackNode));
    if (node)
    {
        node->data = (uintptr_t)node;
        return node;
    }
    *rc = ALLOC_ERROR;
    return NULL;
}

void destroyNode(LinkedStackNode *node)
{
    if (node)
    {
        freedMemory[freedIndex++] = node->data;
        free(node);
    }
}

uintptr_t push(LinkedStack *stack, int *rc)
{
    if (!stack)
    {
        *rc = NULLPTR_ERROR;
        return 0;
    }

    LinkedStackNode *node = linkedStackNode(rc);

    if (!*rc)
    {
        node->next = stack->stackPointer;

        stack->stackPointer = node;
        return node->data;
    }
    return 0;
}

uintptr_t pop(LinkedStack *stack, int *rc)
{
    if (!stack)
    {
        *rc = NULLPTR_ERROR;
        return 0;
    }

    LinkedStackNode *tmp = stack->stackPointer;

    if (tmp)
    {
        stack->stackPointer = tmp->next;
        uintptr_t value = tmp->data;
        destroyNode(tmp);
        return value;
    }

    *rc = EMPTY_STACK_POP;
    return 0;
}

void printFreedMemory(void)
{
    for (size_t i = 0; i < freedIndex; ++i)
        printf("%p\n", (void *)freedMemory[i]);
}
