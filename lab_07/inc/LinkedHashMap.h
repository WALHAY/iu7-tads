#pragma once

#include "../inc/Hash.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR 2
#define MAX_LIST_SIZE 4

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

void freeLinkedHashMap(LinkedHashMap *hashMap);

void printLinkedHashMap(LinkedHashMap *hashMape);
