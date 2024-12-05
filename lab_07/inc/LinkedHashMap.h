#pragma once

#include "../inc/Hash.h"
#include "../inc/PrimeNumber.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR 1.2
#define MAX_LIST_SIZE 10

typedef struct HashMapNode HashMapNode;

struct HashMapNode
{
    int value;
    HashMapNode *next;
};

typedef struct
{
    size_t size;
    HashMapNode **data;
} LinkedHashMap;

int getCompAmountLinked(void);

void clearCompLinked(void);

LinkedHashMap *createLinkedHashMap(size_t size);

void linkedHashMapInsert(LinkedHashMap *hashMap, int value);

bool linkedHashMapRemove(LinkedHashMap *hashMap, int value);

bool linkedHashMapFind(LinkedHashMap *hashMap, int value);

void freeLinkedHashMap(LinkedHashMap **hashMap);

void printLinkedHashMap(LinkedHashMap *hashMape);
