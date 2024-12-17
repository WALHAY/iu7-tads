#pragma once

#include "../inc/Hash.h"
#include "../inc/PrimeNumber.h"
#include <stdbool.h>
#include <string.h>

#define LOAD_FACTOR 1.2
#define MAX_COLLISIONS 5

typedef enum status
{
    NOT_USED,
    USED,
    DELETED
} Status;

typedef struct
{
    int value;
    Status status;
} Pair;

typedef struct
{
    size_t size;
    Pair *data;
} HashMap;

int getCompAmountHash(void);

void clearCompHash(void);

HashMap *createHashMap(size_t size);

void hashMapInsert(HashMap *map, int value);

bool hashMapRemove(HashMap *map, int value);

bool hashMapFind(HashMap *map, int value);

void printHashMap(HashMap *hashMap);

void freeHashMap(HashMap **hashMap);
