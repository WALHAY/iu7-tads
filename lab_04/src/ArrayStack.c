#include "ArrayStack.h"

ArrayStack *arrayStack(size_t init_size, int *rc)
{
    ArrayStack *stack = malloc(sizeof(ArrayStack));
    if (!stack)
    {
        *rc = ALLOC_ERROR;
        return NULL;
    }

    stack->begin = malloc(init_size * sizeof(void *));
    if (!stack->begin)
    {
        *rc = ALLOC_ERROR;
        return NULL;
    }

    stack->end = stack->begin + init_size;
    stack->stackPointer = stack->begin - 1;
    return stack;
}

void destroyStackArr(ArrayStack *stack)
{
    if (stack)
    {
        if (stack->begin)
            free(stack->begin);
        free(stack);
    }
}

uintptr_t pushArr(ArrayStack *stack, uintptr_t ptr, int *rc)
{
    if (stack->stackPointer >= stack->end)
    {
        size_t currentSize = stack->begin - stack->end;
        uintptr_t *newBuf = realloc(stack->begin, currentSize * LOAD_FACTOR * sizeof(uintptr_t));
        if (!newBuf)
            *rc = ALLOC_ERROR;

        stack->begin = newBuf;
    }

    stack->stackPointer++;
    *stack->stackPointer = ptr;
    return ptr;
}

uintptr_t popArr(ArrayStack *stack, int *rc)
{
    if (stack->stackPointer >= stack->begin)
        return *stack->stackPointer--;
    else
        *rc = EMPTY_STACK_POP;

    return 0;
}
