#include "../inc/LinkedHashMap.h"
#include <stdio.h>

static int comp = 0;

int getCompAmountLinked(void)
{
    return comp;
}

void clearCompLinked(void)
{
    comp = 0;
}

static HashMapNode *createHashMapNode(int value)
{
    HashMapNode *node = malloc(sizeof(HashMapNode));
    if (node)
    {
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
        head = head->next;
        size++;
    }
    head->next = node;
    return size;
}

static HashMapNode *listFind(HashMapNode *head, int value)
{
    while (head)
    {
        if (head->value == value)
            return head;
        head = head->next;
    }
    return NULL;
}

static size_t linkedHashMapInsertNode(LinkedHashMap *hashMap, HashMapNode *node)
{
    comp++;
    hash_t keyHash = getIntHash(node->value);
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

void linkedHashMapInsert(LinkedHashMap *hashMap, int value)
{
    if (linkedHashMapInsertNode(hashMap, createHashMapNode(value)) >= MAX_LIST_SIZE)
        rebuildLinkedHashMap(hashMap);
}

bool linkedHashMapFind(LinkedHashMap *hashMap, int value)
{
    hash_t keyHash = getIntHash(value);
    size_t index = keyHash % hashMap->size;

    return listFind(hashMap->data[index], value);
}

static void freeNode(HashMapNode *node)
{
    if (node)
        free(node);
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
        printf("Hash: %llu\nValue: %d\n\n", getIntHash(node->value), node->value);
}

void printLinkedHashMap(LinkedHashMap *hashMap)
{
    for (size_t i = 0; i < hashMap->size; ++i)
        printNode(hashMap->data[i]);
}
