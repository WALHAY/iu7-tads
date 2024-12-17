#include "../inc/HashMap.h"
#include <stdio.h>

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
        map->data = calloc(size, sizeof(Pair));
    }
    return map;
}

static void rebuildHashMap(HashMap *map)
{
    size_t oldSize = map->size;
    const Pair *oldData = map->data;
    map->size = getNextPrime(map->size * LOAD_FACTOR);
    map->data = calloc(map->size, sizeof(Pair));

    for (size_t i = 0; i < oldSize; ++i)
        if (oldData[i].status == USED)
            hashMapInsert(map, oldData[i].value);
}

void hashMapInsert(HashMap *map, int value)
{
    hash_t hash = getIntHash(value);

    size_t index = hash % map->size;

    for (size_t offset = 0; offset < MAX_COLLISIONS; ++offset)
    {
        size_t cyclicIndex = (index + offset) % map->size;
        Status status = map->data[cyclicIndex].status;
        if (status == USED)
        {
            comp++;
            if (map->data[cyclicIndex].value == value)
                return;
        }
        else
        {
            map->data[cyclicIndex] = (Pair){value, USED};
            return;
        }
    }
    rebuildHashMap(map);
    hashMapInsert(map, value);
}

bool hashMapRemove(HashMap *map, int value)
{
    hash_t hash = getIntHash(value);
    size_t index = hash % map->size;
    for (size_t offset = 0; offset < MAX_COLLISIONS; ++offset)
    {
        size_t cyclicIndex = (index + offset) % map->size;
        comp++;
        Status status = map->data[cyclicIndex].status;
        if (status == DELETED)
            continue;

        if (status == USED && map->data[cyclicIndex].value == value)
        {
            map->data[cyclicIndex].status = DELETED;
            return true;
        }
    }
    return false;
}

bool hashMapFind(HashMap *map, int value)
{
    hash_t hash = getIntHash(value);

    size_t index = hash % map->size;

    for (size_t offset = 0; offset < MAX_COLLISIONS; ++offset)
    {
        size_t localIndex = (index + offset) % map->size;
        if (map->data[localIndex].status == NOT_USED)
            break;

        if (map->data[localIndex].status == DELETED)
            continue;

        comp++;
        if (value == map->data[localIndex].value)
            return true;
    }

    return false;
}

void printHashMap(HashMap *hashMap)
{
    printf("Current size: %zu\n", hashMap->size);
    for (size_t i = 0; i < hashMap->size; ++i)
        if (hashMap->data[i].status == USED)
            printf("Hash: %llu(%zu)\nValue: %d\n\n", getIntHash(hashMap->data[i].value) % hashMap->size, i,
                   hashMap->data[i].value);
}

void freeHashMap(HashMap **hashMap)
{
    if (hashMap && *hashMap)
    {
        free((*hashMap)->data);
        free(*hashMap);
        *hashMap = NULL;
    }
}
