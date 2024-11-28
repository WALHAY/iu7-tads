#pragma once

#include "../inc/Hash.h"
#include <stdbool.h>
#include <string.h>

typedef struct
{
    const char *key;
    int value;
} MapEntry;

typedef struct
{
    size_t size;
    MapEntry **data;
} HashMap;

HashMap *createHashMap(size_t size);

void hashMapInsert(HashMap *map, const char *key, int value);

bool hashMapFind(HashMap *map, const char *key, int *value);
