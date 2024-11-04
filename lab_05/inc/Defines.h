#pragma once

typedef enum
{
    SUCCESS = 0,
    NULLPTR_ERROR,
    ALLOC_ERROR,
    NAN_ERROR,
    EMPTY_QUEUE_POP,
    PUSH_FULL_ARR_QUEUE
} ERRORS;

typedef enum
{
    EXIT
} OPCODES;
