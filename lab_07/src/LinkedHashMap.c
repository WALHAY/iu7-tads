#include "../inc/LinkedHashMap.h"

static HashMapNode *createHashMapNode(const char *key, int value)
{
    HashMapNode *node = malloc(sizeof(HashMapNode));
    if (node)
    {
        node->key = strdup(key);
        node->value = value;
        node->next = NULL;
    }
    return node;
}

LinkedHashMap *createLinkedHashMap(size_t size)
{
    LinkedHashMap *map = malloc(sizeof(LinkedHashMap));
    if (map)
    {
        map->data = calloc(size, sizeof(HashMapNode *));
        map->size = size;
    }
    return map;
}

static HashMapNode *listInsert(HashMapNode *head, const char *key, int value)
{
    if (!head)
        return createHashMapNode(key, value);

    if (!strcmp(head->key, key))
        return head;

    head->next = listInsert(head->next, key, value);

    return head;
}

static HashMapNode *listFind(HashMapNode *head, const char *key)
{
    if (!head)
        return NULL;

    if (!strcmp(key, head->key))
        return head;

    return listFind(head->next, key);
}

void linkedHashMapInsert(LinkedHashMap *hashMap, const char *key, int value)
{
    hash_t keyHash = getStringHash(key);
    size_t index = keyHash % hashMap->size;

    hashMap->data[index] = listInsert(hashMap->data[index], key, value);
}

bool linkedHashMapFind(LinkedHashMap *hashMap, const char *key, int *value)
{
    hash_t keyHash = getStringHash(key);
    size_t index = keyHash % hashMap->size;

    HashMapNode *node = listFind(hashMap->data[index], key);
    *value = node ? node->value : 0;
    return node;
}
