#include "../inc/ArrayStack.h"

ArrayStack *arrayStack(int *rc)
{
    ArrayStack *stack = malloc(sizeof(ArrayStack));
    if (!stack)
    {
        *rc = ALLOC_ERROR;
        return NULL;
    }

    uintptr_t static_arr[ARR_SIZE];
    stack->begin = static_arr;
    if (!stack->begin)
    {
        *rc = ALLOC_ERROR;
        return NULL;
    }

    stack->end = stack->begin + ARR_SIZE;
    stack->stackPointer = stack->begin - 1;
    return stack;
}

void destroyStackArr(ArrayStack *stack)
{
    if (stack)
        free(stack);
}

uintptr_t pushArr(ArrayStack *stack, uintptr_t ptr, int *rc)
{
    if (stack->stackPointer >= stack->end)
    {
        *rc = STACK_OVERFLOW;
        return 0;
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
