#pragma once

#include "../inc/Hash.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashMapNode HashMapNode;

struct HashMapNode
{
    const char *key;
    int value;
    HashMapNode *next;
};

typedef struct
{
    size_t size;
    HashMapNode **data;
} LinkedHashMap;

LinkedHashMap *createLinkedHashMap(size_t size);

void linkedHashMapInsert(LinkedHashMap *hashMap, const char *key, int value);

bool linkedHashMapFind(LinkedHashMap *hashMap, const char *key, int *value);
