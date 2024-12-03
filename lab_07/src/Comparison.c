#include "../inc/Comparison.h"
#include "../inc/Defines.h"

static char *randomString(int value)
{
    char string[255];

    size_t index = 0;
    while (value > 0)
    {
        string[index++] = value % 10 + 'a';
        value /= 10;
    }
    string[index] = 0;

    return strdup(string);
}

typedef struct
{
    char *key;
    int value;
} Pair;

static void generatePairs(size_t size, Pair *pairs)
{
    for (size_t i = 0; i < size; ++i)
    {
        int value = rand();
        char *key = randomString(value);
        pairs[i] = (Pair){key, value};
    }
}

void getBinTreeData(size_t size)
{
    struct timespec t1, t2;

    size_t mem = sizeof(TreeNode) * size;

    Pair pairs[size];
    generatePairs(size, pairs);

    TreeNode *node = NULL;

    size_t avg_insert = 0;
    for (size_t i = 0; i < size; ++i)
    {

        char *key = pairs[i].key;
        int value = pairs[i].value;
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        node = treeInsert(node, key, value);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    avg_insert /= size;

    size_t avg_find = 0;
    for (size_t i = 0; i < size; ++i)
    {

        char *key = pairs[i].key;
        int value = 0;
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        treeFind(node, key, &value);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    avg_find /= size;

    printf("%zu\t%zu\t%zu\t%zu\t%zu\n", size, mem, avg_insert, avg_find, 0UL);
}

void getAvlTreeData(size_t size)
{
    struct timespec t1, t2;

    size_t mem = sizeof(AVLTreeNode) * size;

    Pair pairs[size];
    generatePairs(size, pairs);

    AVLTreeNode *node = NULL;

    size_t avg_insert = 0;
    for (size_t i = 0; i < size; ++i)
    {

        char *key = pairs[i].key;
        int value = pairs[i].value;
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        node = avlTreeInsert(node, key, value);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    avg_insert /= size;

    size_t avg_find = 0;
    for (size_t i = 0; i < size; ++i)
    {
        char *key = pairs[i].key;
        int value = 0;
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        avlTreeFind(node, key, &value);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    avg_find /= size;

    printf("%zu\t%zu\t%zu\t%zu\t%zu\n", size, mem, avg_insert, avg_find, 0UL);
}

void getOpenHashMapData(size_t size)
{
    struct timespec t1, t2;

    Pair pairs[size];
    generatePairs(size, pairs);

    LinkedHashMap *linkedHashMap = createLinkedHashMap(INITIAL_SIZE);

    size_t avg_insert = 0;
    for (size_t i = 0; i < size; ++i)
    {

        char *key = pairs[i].key;
        int value = pairs[i].value;
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        linkedHashMapInsert(linkedHashMap, key, value);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    avg_insert /= size;

    size_t avg_find = 0;
    for (size_t i = 0; i < size; ++i)
    {
        char *key = pairs[i].key;
        int value = 0;
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        linkedHashMapFind(linkedHashMap, key, &value);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    avg_find /= size;

    size_t mem = sizeof(HashMap) + sizeof(MapEntry) * linkedHashMap->size;

    printf("%zu\t%zu\t%zu\t%zu\t%zu\n", size, mem, avg_insert, avg_find, 0UL);
}

void getClosedHashMapData(size_t size)
{
    struct timespec t1, t2;

    Pair pairs[size];
    generatePairs(size, pairs);

    HashMap *hashMap = createHashMap(INITIAL_SIZE);

    size_t avg_insert = 0;
    for (size_t i = 0; i < size; ++i)
    {

        char *key = pairs[i].key;
        int value = pairs[i].value;
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        hashMapInsert(hashMap, key, value);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    avg_insert /= size;

    size_t avg_find = 0;
    for (size_t i = 0; i < size; ++i)
    {

        char *key = pairs[i].key;
        int value = 0;
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        hashMapFind(hashMap, key, &value);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    avg_find /= size;

    size_t mem = sizeof(HashMap) + sizeof(MapEntry) * hashMap->size;

    printf("%zu\t%zu\t%zu\t%zu\t%zu\n", size, mem, avg_insert, avg_find, 0UL);
}

void compareTaDS()
{
    printf("Type\t\tSize\tMemory\tInsert\tFind\tComparisons\n");
    printf("Bin Tree\t");
    getBinTreeData(500);
    printf("AVL Tree\t");
    getAvlTreeData(500);
    printf("Open Hash Map\t");
    getOpenHashMapData(500);
    printf("Closed Hash Map\t");
    getClosedHashMapData(500);
}
