#pragma once

typedef enum
{
    SUCCESS = 0,
    NULLPTR_ERROR,
    ALLOC_ERROR,
    NAN_ERROR
} ERRORS;

typedef enum
{
    ADD,
    FIND,
    REMOVE,
    PRINT,
    REMOVE_LOW,
    COMPARE_TADS,
    EXIT
} OPCODES;
