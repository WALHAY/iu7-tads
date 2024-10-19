#pragma once

#define MAX_FULL_MATRIX_INPUT_LEN 10
#define MAX_FULL_VECTOR_INPUT_LEN 30

typedef enum
{
    SUCCESS = 0,
    WRONG_SIZE_ERROR,
    NULLPTR_ERROR,
    ALLOC_ERROR
} ERRORS;

typedef enum
{
    EXIT
} OPCODES;
