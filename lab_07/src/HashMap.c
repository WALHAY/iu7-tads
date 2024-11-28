#include "../inc/HashMap.h"

#define MAX_OFFSET 5

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

void hashMapInsert(HashMap *map, const char *key, int value)
{
    hash_t hash = getStringHash(key);

    size_t index = hash % map->size;

    while (map->data[index] != NULL)
        index++;

    map->data[index] = createMapEntry(key, value);
}

bool hashMapFind(HashMap *map, const char *key, int *value)
{
    hash_t hash = getStringHash(key);

    size_t index = hash % map->size;

    for (size_t offset = 0; offset < MAX_OFFSET && index + offset < map->size; ++offset)
    {
        if (!strcmp(map->data[index + offset]->key, key))
        {
            *value = map->data[index + offset]->value;
            return true;
        }
    }

    return false;
}
