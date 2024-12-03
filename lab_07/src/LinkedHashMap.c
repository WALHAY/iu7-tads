#include "../inc/LinkedHashMap.h"
#include <stdio.h>

static int coll = 0;

int getCollAmountLinked(void)
{
    return coll;
}

void clearCollLinked(void)
{
    coll = 0;
}

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

static size_t listInsert(HashMapNode **head_ptr, HashMapNode *node)
{
    if (!*head_ptr)
    {
        *head_ptr = node;
        return 1;
    }

    size_t size = 1;
    HashMapNode *head = *head_ptr;
    while (head && head->next)
    {
        coll++;
        head = head->next;
        size++;
    }
    head->next = node;
    return size;
}

static HashMapNode *listFind(HashMapNode *head, const char *key)
{
    while (head)
    {
        if (!strcmp(key, head->key))
            return head;
        head = head->next;
    }
    return NULL;
}

static size_t linkedHashMapInsertNode(LinkedHashMap *hashMap, HashMapNode *node)
{
    hash_t keyHash = getStringHash(node->key);
    size_t index = keyHash % hashMap->size;
    return listInsert(&hashMap->data[index], node);
}

static void rebuildLinkedHashMap(LinkedHashMap *hashMap)
{
    size_t oldSize = hashMap->size;
    HashMapNode **oldData = hashMap->data;

    hashMap->size *= LOAD_FACTOR;
    hashMap->data = calloc(hashMap->size, sizeof(HashMapNode *));

    for (size_t i = 0; i < oldSize; ++i)
    {
        HashMapNode *node = oldData[i];
        while (node)
        {
            HashMapNode *next = node->next;
            node->next = NULL;

            linkedHashMapInsertNode(hashMap, node);

            node = next;
        }
    }
}

void linkedHashMapInsert(LinkedHashMap *hashMap, const char *key, int value)
{
    if (linkedHashMapInsertNode(hashMap, createHashMapNode(key, value)) >= MAX_LIST_SIZE)
        rebuildLinkedHashMap(hashMap);
}

bool linkedHashMapFind(LinkedHashMap *hashMap, const char *key, int *value)
{
    hash_t keyHash = getStringHash(key);
    size_t index = keyHash % hashMap->size;

    HashMapNode *node = listFind(hashMap->data[index], key);
    *value = node ? node->value : 0;
    return node;
}

static void freeNode(HashMapNode *node)
{
    if (node)
    {
        if (node->key)
            free((char *)node->key);
        free(node);
    }
}

static void freeList(HashMapNode *node)
{
    if (node)
    {
        freeList(node->next);
        freeNode(node);
    }
}

void freeLinkedHashMap(LinkedHashMap **hashMap)
{
    if (hashMap && *hashMap)
    {
        for (size_t i = 0; i < (*hashMap)->size; ++i)
            freeList((*hashMap)->data[i]);
        *hashMap = NULL;
    }
}

static void printNode(HashMapNode *node)
{
    if (node)
        printf("Hash: %llu\nKey: %s\nValue: %d\n", getStringHash(node->key), node->key, node->value);
}

void printLinkedHashMap(LinkedHashMap *hashMap)
{
    for (size_t i = 0; i < hashMap->size; ++i)
        printNode(hashMap->data[i]);
}
