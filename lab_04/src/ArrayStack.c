#include "../inc/ArrayStack.h"

ArrayStack *arrayStack(size_t init_size)
{
    ArrayStack *stack = malloc(sizeof(ArrayStack));
    if (stack)
    {
        stack->begin = malloc(init_size * sizeof(void *));
        stack->end = stack->begin + init_size;
        stack->stackPointer = stack->begin - 1;
    }
    return stack;
}

uintptr_t push_arr(ArrayStack *stack, uintptr_t ptr)
{
    if (stack->stackPointer >= stack->end)
    {
        size_t currentSize = stack->begin - stack->end;
        uintptr_t *newBuf = realloc(stack->begin, currentSize * LOAD_FACTOR * sizeof(uintptr_t));
        if (newBuf)
            stack->begin = newBuf;
    }

    stack->stackPointer++;
    *stack->stackPointer = ptr;
    return ptr;
}

uintptr_t pop_arr(ArrayStack *stack)
{
    if (stack->stackPointer >= stack->begin)
        return *stack->stackPointer--;

    return 0;
}
