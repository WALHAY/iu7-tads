#pragma once

typedef enum
{
    SUCCESS = 0,
    NULLPTR_ERROR,
    ALLOC_ERROR,
    NAN_ERROR,
    EMPTY_GRAPH
} ERRORS;

typedef enum
{
    ADD,
    FIND,
    REMOVE,
    PRINT,
    SHOW_GRAPH,
    REMOVE_LOW,
    COMPARE_TADS,
    EXIT
} OPCODES;
