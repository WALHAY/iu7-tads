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
        if (oldData[i].used)
            hashMapInsert(map, oldData[i].value);
}

void hashMapInsert(HashMap *map, int value)
{
    hash_t hash = getIntHash(value);

    size_t index = hash % map->size;

    for (size_t offset = 0; offset < MAX_COLLISIONS; ++offset)
    {
        size_t cyclicIndex = (index + offset) % map->size;
        if (map->data[cyclicIndex].used)
        {
            comp++;
            if (map->data[cyclicIndex].value == value)
                return;
        }
        else
        {
            map->data[cyclicIndex] = (Pair){value, true};
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
        if (map->data[cyclicIndex].used && map->data[cyclicIndex].value == value)
        {
            map->data[cyclicIndex].used = false;
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
        if (!map->data[index].used)
            break;

        comp++;
        if (value == map->data[(index + offset) % map->size].value)
            return true;
    }

    return false;
}

void printHashMap(HashMap *hashMap)
{
    printf("Current size: %zu\n", hashMap->size);
    for (size_t i = 0; i < hashMap->size; ++i)
        if (hashMap->data[i].used)
            printf("Hash: %llu\nValue: %d\n\n", getIntHash(hashMap->data[i].value) % hashMap->size,
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
