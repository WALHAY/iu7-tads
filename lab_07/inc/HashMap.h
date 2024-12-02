#pragma once

#include "../inc/Hash.h"
#include <stdbool.h>
#include <string.h>

#define LOAD_FACTOR 2
#define MAX_FAILS 4

typedef struct
{
    const char *key;
    int value;
} MapEntry;

typedef struct
{
    size_t size;
    const MapEntry **data;
} HashMap;

HashMap *createHashMap(size_t size);

void hashMapInsert(HashMap *map, const char *key, int value);

bool hashMapFind(HashMap *map, const char *key, int *value);

void printHashMap(HashMap *hashMap);

void freeHashMap(HashMap **hashMap);
