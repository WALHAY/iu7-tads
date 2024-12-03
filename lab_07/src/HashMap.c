#include "../inc/HashMap.h"
#include <stdio.h>

#define MAX_OFFSET 5

static int comp = 0;

int getCompAmountHash(void)
{
    return comp;
}

void clearCompHash(void)
{
    comp = 0;
}

HashMap *createHashMap(size_t size)
{
    HashMap *map = malloc(sizeof(HashMap));
    if (map)
    {
        map->size = size;
        map->data = calloc(size, sizeof(int));
    }
    return map;
}

static size_t hashMapInsertValue(HashMap *map, int value)
{
    comp++;
    size_t fails = 0;

    hash_t hash = getIntHash(value);

    size_t index = hash % map->size;
    while (map->data[index + fails])
    {
        if (++fails + index > map->size || fails >= MAX_FAILS)
            return MAX_FAILS;
    }

    map->data[index + fails] = value;
    return fails;
}

static void rebuildHashMap(HashMap *map)
{
    size_t oldSize = map->size;
    const int *oldData = map->data;
    map->size *= LOAD_FACTOR;
    map->data = calloc(map->size, sizeof(int));

    for (size_t i = 0; i < oldSize; ++i)
        hashMapInsertValue(map, oldData[i]);
}

void hashMapInsert(HashMap *map, int value)
{
    if (hashMapInsertValue(map, value) >= MAX_FAILS)
        rebuildHashMap(map);
}

bool hashMapFind(HashMap *map, int value)
{
    hash_t hash = getIntHash(value);

    size_t index = hash % map->size;

    for (size_t offset = 0; offset < MAX_FAILS && index + offset < map->size; ++offset)
        if (value == map->data[index + offset])
            return true;

    return false;
}

void printHashMap(HashMap *hashMap)
{
}

void freeHashMap(HashMap **hashMap)
{
    if (hashMap && *hashMap)
    {
        for (size_t i = 0; i < (*hashMap)->size; ++i)
        {
        }
        *hashMap = NULL;
    }
}
