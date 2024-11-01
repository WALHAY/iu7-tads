#pragma once

typedef enum
{
    SUCCESS = 0,
    NULLPTR_ERROR,
    ALLOC_ERROR,
    NAN_ERROR,
    EMPTY_STACK_POP,
    STACK_OVERFLOW
} ERRORS;

typedef enum
{
    ARR_PUSH,
    ARR_POP,
    LINKED_PUSH,
    LINKED_POP,
    COMPARISON,
    PRINT_FREED,
    EXIT
} OPCODES;
