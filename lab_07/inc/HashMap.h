#pragma once

#include "../inc/Hash.h"
#include <stdbool.h>
#include <string.h>

#define LOAD_FACTOR 2
#define MAX_FAILS 4

typedef struct
{
    size_t size;
    int *data;
} HashMap;

int getCompAmountHash(void);

void clearCompHash(void);

HashMap *createHashMap(size_t size);

void hashMapInsert(HashMap *map, int value);

bool hashMapFind(HashMap *map, int value);

void printHashMap(HashMap *hashMap);

void freeHashMap(HashMap **hashMap);
