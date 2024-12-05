#include "../inc/Comparison.h"

#define TRIES 50

static void fillArray(size_t size, int *array)
{
    srand(rand());
    for (size_t i = 0; i < size; ++i)
        array[i] = rand();
}

void getBinTreeData(size_t size)
{
    struct timespec t1, t2;

    size_t mem = sizeof(TreeNode) * size;

    Pair pairs[size];
    size_t avg_insert = 0;
    size_t avg_comp = 0;
    size_t avg_find = 0;
    int arr[size];
    for (size_t j = 0; j < TRIES; ++j)
    {
        TreeNode *node = NULL;
        fillArray(size, arr);

        for (size_t i = 0; i < size; ++i)
        {
            clearComp();
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            node = treeInsert(node, arr[i]);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
            avg_comp += getCompAmount();
        }

        for (size_t i = 0; i < size; ++i)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            treeFind(node, arr[i]);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
        }
    }

    printf("%zu\t%zu\t%zu\t%zu\t%zu\n", size, mem, avg_insert / size / TRIES, avg_find / size / TRIES,
           avg_comp / size / TRIES);
}

void getAvlTreeData(size_t size)
{
    struct timespec t1, t2;

    size_t mem = sizeof(AVLTreeNode) * size;

    size_t avg_insert = 0;
    size_t avg_comp = 0;
    size_t avg_find = 0;
    int arr[size];
    for (size_t j = 0; j < TRIES; ++j)
    {
        fillArray(size, arr);
        AVLTreeNode *node = NULL;
        for (size_t i = 0; i < size; ++i)
        {
            clearCompAvl();
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            node = avlTreeInsert(node, arr[i]);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
            avg_comp += getCompAmountAvl();
        }

        for (size_t i = 0; i < size; ++i)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            avlTreeFind(node, arr[i]);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
        }
    }

    printf("%zu\t%zu\t%zu\t%zu\t%zu\n", size, mem, avg_insert / size / TRIES, avg_find / size / TRIES,
           avg_comp / size / TRIES);
}

void getOpenHashMapData(size_t size)
{
    struct timespec t1, t2;

    size_t avg_insert = 0;
    size_t avg_comp = 0;
    size_t avg_find = 0;
    int arr[size];
    for (size_t j = 0; j < TRIES; ++j)
    {
        LinkedHashMap *linkedHashMap = createLinkedHashMap(INITIAL_SIZE);
        fillArray(size, arr);
        for (size_t i = 0; i < size; ++i)
        {
            clearCompLinked();
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            linkedHashMapInsert(linkedHashMap, arr[i]);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
            avg_comp += getCompAmountLinked();
        }

        for (size_t i = 0; i < size; ++i)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            linkedHashMapFind(linkedHashMap, arr[i]);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
        }
    }

    size_t mem = sizeof(LinkedHashMap) + sizeof(HashMapNode) * size;

    printf("%zu\t%zu\t%zu\t%zu\t%zu\n", size, mem, avg_insert / size / TRIES, avg_find / size / TRIES,
           avg_comp / size / TRIES);
}

void getClosedHashMapData(size_t size)
{
    struct timespec t1, t2;

    Pair pairs[size];

    size_t avg_insert = 0;
    size_t avg_comp = 0;
    size_t avg_find = 0;
    size_t mem = 0;
    int arr[size];
    for (size_t j = 0; j < TRIES; ++j)
    {
        HashMap *hashMap = createHashMap(INITIAL_SIZE);
        fillArray(size, arr);
        for (size_t i = 0; i < size; ++i)
        {
            clearCompHash();
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            hashMapInsert(hashMap, arr[i]);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
            avg_comp += getCompAmountHash();
        }

        for (size_t i = 0; i < size; ++i)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            hashMapFind(hashMap, arr[i]);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
        }
        mem += sizeof(HashMap) + sizeof(Pair) * hashMap->size;
    }

    printf("%zu\t%zu\t%zu\t%zu\t%zu\n", size, mem / TRIES, avg_insert / size / TRIES, avg_find / size / TRIES,
           avg_comp / size / TRIES);
}

void compareTaDS(void)
{
    size_t n = 500;
    printf("Type\t\tSize\tMemory\tInsert\tFind\tOperations\n");
    printf("Bin Tree\t");
    getBinTreeData(n);
    printf("AVL Tree\t");
    getAvlTreeData(n);
    printf("Open Hash Map\t");
    getOpenHashMapData(n);
    printf("Closed Hash Map\t");
    getClosedHashMapData(n);
    n = 5000;
    printf("\n\nType\t\tSize\tMemory\tInsert\tFind\tOperations\n");
    printf("Bin Tree\t");
    getBinTreeData(n);
    printf("AVL Tree\t");
    getAvlTreeData(n);
    printf("Open Hash Map\t");
    getOpenHashMapData(n);
    printf("Closed Hash Map\t");
    getClosedHashMapData(n);
}
