#pragma once

#define INITIAL_SIZE 8

typedef enum
{
    SUCCESS = 0,
    NULLPTR_ERROR,
    ALLOC_ERROR,
    NAN_ERROR,
    IO_ERROR
} ERRORS;

typedef enum
{
    FROM_FILE,
    NEW,
    ADD,
    FIND,
    REMOVE,
    PRINT,
    COMPARISON,
    EXIT
} OPCODES;
