#pragma once

#define MAX_FULL_MATRIX_INPUT_LEN 10
#define MAX_FULL_VECTOR_INPUT_LEN 30

typedef enum
{
    SUCCESS = 0,
    NULLPTR_ERROR,
    ALLOC_ERROR,
    NAN_ERROR,
    EMPTY_STACK_POP
} ERRORS;

typedef enum
{
    ARR_PUSH,
    ARR_POP,
    LINKED_PUSH,
    LINKED_POP,
    COMPARISON,
    EXIT
} OPCODES;
