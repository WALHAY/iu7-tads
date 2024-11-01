#pragma once

typedef enum
{
    SUCCESS = 0,
    NULLPTR_ERROR,
    ALLOC_ERROR,
    NAN_ERROR,
    EMPTY_QUEUE_POP
} ERRORS;

typedef enum
{
    EXIT
} OPCODES;
