#include "../inc/HashMap.h"
#include <stdio.h>

#define MAX_OFFSET 5

static int coll = 0;

int getCollAmount(void)
{
    return coll;
}

void clearColl(void)
{
    coll = 0;
}

static MapEntry *createMapEntry(const char *key, int value)
{
    MapEntry *entry = malloc(sizeof(MapEntry));
    if (entry)
    {
        entry->key = strdup(key);
        entry->value = value;
    }
    return entry;
}

HashMap *createHashMap(size_t size)
{
    HashMap *map = malloc(sizeof(HashMap));
    if (map)
    {
        map->size = size;
        map->data = calloc(size, sizeof(MapEntry *));
    }
    return map;
}

static size_t hashMapInsertEntry(HashMap *map, const MapEntry *entry)
{
    size_t fails = 0;

    hash_t hash = getStringHash(entry->key);

    size_t index = hash % map->size;
    while (index + fails < map->size && map->data[index + fails] != NULL)
    {
        const MapEntry *local = map->data[index + fails];
        if (!strcmp(entry->key, local->key))
            return 0;
        fails++;
    }

    map->data[index + fails] = entry;
    return index + fails >= map->size ? MAX_FAILS : fails;
}

static void rebuildHashMap(HashMap *map)
{
    size_t oldSize = map->size;
    const MapEntry **oldEntries = map->data;
    map->size *= LOAD_FACTOR;
    map->data = calloc(map->size, sizeof(MapEntry *));

    for (size_t i = 0; i < oldSize; ++i)
    {
        const MapEntry *entry = oldEntries[i];
        if (entry)
            hashMapInsertEntry(map, entry);
    }
}

void hashMapInsert(HashMap *map, const char *key, int value)
{
    if (hashMapInsertEntry(map, createMapEntry(key, value)) >= MAX_FAILS)
        rebuildHashMap(map);
}

bool hashMapFind(HashMap *map, const char *key, int *value)
{
    hash_t hash = getStringHash(key);

    size_t index = hash % map->size;

    for (size_t offset = 0; offset < MAX_OFFSET && index + offset < map->size && map->data[index + offset]; ++offset)
    {
        if (!strcmp(map->data[index + offset]->key, key))
        {
            *value = map->data[index + offset]->value;
            return true;
        }
    }

    return false;
}

static void printMapEntry(const MapEntry *entry)
{
    if (entry)
        printf("Hash: %llu\nKey: %s\nValue: %d\n", getStringHash(entry->key), entry->key, entry->value);
}

void printHashMap(HashMap *hashMap)
{
    for (size_t i = 0; i < hashMap->size; ++i)
        printMapEntry(hashMap->data[i]);
}

void freeHashMap(HashMap **hashMap)
{
    if (hashMap && *hashMap)
    {
        for (size_t i = 0; i < (*hashMap)->size; ++i)
        {
            const MapEntry *entry = (*hashMap)->data[i];
            printMapEntry(entry);
        }
        *hashMap = NULL;
    }
}

