#pragma once

#define INITIAL_SIZE 8

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
    CLOSED_HASH_MAP,
    OPEN_HASH_MAP,
    AVL_TREE,
    BIN_TREE,
    COMPARISON,
    EXIT
} OPCODES;

typedef enum
{
    FROM_FILE,
    NEW,
    ADD,
    FIND,
    PRINT,
    MAP_BACK
} HASHMAP_OPS;

typedef enum
{
    TFROM_FILE,
    TNEW,
    TADD,
    TFIND,
    TREMOVE,
    TDRAW,
    TBACK
} TREE_OPS;
