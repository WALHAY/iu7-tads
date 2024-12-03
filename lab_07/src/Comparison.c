// #include "../inc/Comparison.h"

// #define TRIES 50

// static char *randomString(int value)
// {
//     char string[255];

//     size_t index = 0;
//     while (value > 0)
//     {
//         string[index++] = value % 10 + 'a';
//         value /= 10;
//     }
//     string[index] = 0;

//     return strdup(string);
// }

// typedef struct
// {
//     char *key;
//     int value;
// } Pair;

// static void generatePairs(size_t size, Pair *pairs)
// {
//     srand(rand());
//     for (size_t i = 0; i < size; ++i)
//     {
//         int value = rand();
//         char *key = randomString(value);
//         pairs[i] = (Pair){key, value};
//     }
// }

// void getBinTreeData(size_t size)
// {
//     struct timespec t1, t2;

//     size_t mem = sizeof(TreeNode) * size;

//     Pair pairs[size];
//     size_t avg_insert = 0;
//     size_t avg_comp = 0;
//     size_t avg_find = 0;
//     for (size_t j = 0; j < TRIES; ++j)
//     {
//         TreeNode *node = NULL;
//         generatePairs(size, pairs);

//         for (size_t i = 0; i < size; ++i)
//         {
//             clearComp();
//             char *key = pairs[i].key;
//             int value = pairs[i].value;
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//             node = treeInsert(node, key, value);
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
//             avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
//             avg_comp += getCompAmount();
//         }

//         for (size_t i = 0; i < size; ++i)
//         {

//             char *key = pairs[i].key;
//             int value = 0;
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//             treeFind(node, key);
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
//             avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
//         }
//     }

//     printf("%zu\t%zu\t%zu\t%zu\t%zu\t-\n", size, mem, avg_insert / size / TRIES, avg_find / size / TRIES,
//            avg_comp / TRIES);
// }

// void getAvlTreeData(size_t size)
// {
//     struct timespec t1, t2;

//     size_t mem = sizeof(AVLTreeNode) * size;

//     Pair pairs[size];

//     size_t avg_insert = 0;
//     size_t avg_comp = 0;
//     size_t avg_find = 0;
//     for (size_t j = 0; j < TRIES; ++j)
//     {
//         AVLTreeNode *node = NULL;
//         generatePairs(size, pairs);
//         for (size_t i = 0; i < size; ++i)
//         {
//             clearCompAvl();
//             char *key = pairs[i].key;
//             int value = pairs[i].value;
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//             node = avlTreeInsert(node, key, value);
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
//             avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
//             avg_comp += getCompAmountAvl();
//         }

//         for (size_t i = 0; i < size; ++i)
//         {
//             char *key = pairs[i].key;
//             int value = 0;
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//             avlTreeFind(node, key);
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
//             avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
//         }
//     }

//     printf("%zu\t%zu\t%zu\t%zu\t%zu\t-\n", size, mem, avg_insert / size / TRIES, avg_find / size / TRIES,
//            avg_comp / TRIES);
// }

// void getOpenHashMapData(size_t size)
// {
//     struct timespec t1, t2;

//     Pair pairs[size];

//     size_t avg_insert = 0;
//     size_t avg_comp = 0;
//     size_t avg_find = 0;
//     for (size_t j = 0; j < TRIES; ++j)
//     {
//         LinkedHashMap *linkedHashMap = createLinkedHashMap(INITIAL_SIZE);
//         generatePairs(size, pairs);
//         for (size_t i = 0; i < size; ++i)
//         {
//             clearCompLinked();
//             char *key = pairs[i].key;
//             int value = pairs[i].value;
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//             linkedHashMapInsert(linkedHashMap, key, value);
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
//             avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
//             avg_comp += getCompAmountLinked();
//         }

//         for (size_t i = 0; i < size; ++i)
//         {
//             char *key = pairs[i].key;
//             int value = 0;
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//             linkedHashMapFind(linkedHashMap, key, &value);
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
//             avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
//         }
//     }

//     size_t mem = sizeof(LinkedHashMap) + sizeof(HashMapNode) * size;

//     printf("%zu\t%zu\t%zu\t%zu\t%zu\n", size, mem, avg_insert / size / TRIES, avg_find / size / TRIES,
//            avg_comp / TRIES);
// }

// void getClosedHashMapData(size_t size)
// {
//     struct timespec t1, t2;

//     Pair pairs[size];

//     size_t avg_insert = 0;
//     size_t avg_comp = 0;
//     size_t avg_find = 0;
//     size_t mem = 0;
//     for (size_t j = 0; j < TRIES; ++j)
//     {
//         generatePairs(size, pairs);
//         HashMap *hashMap = createHashMap(INITIAL_SIZE);
//         for (size_t i = 0; i < size; ++i)
//         {
//             clearCompHash();
//             char *key = pairs[i].key;
//             int value = pairs[i].value;
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//             hashMapInsert(hashMap, key, value);
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
//             avg_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
//             avg_comp += getCompAmountHash();
//         }

//         for (size_t i = 0; i < size; ++i)
//         {
//             char *key = pairs[i].key;
//             int value = 0;
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//             hashMapFind(hashMap, value);
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
//             avg_find += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
//         }
//         mem += sizeof(HashMap) + sizeof(MapEntry) * hashMap->size;
//     }

//     printf("%zu\t%zu\t%zu\t%zu\t%zu\n", size, mem / TRIES, avg_insert / size / TRIES, avg_find / size / TRIES,
//            avg_comp / TRIES);
// }

void compareTaDS(void)
{
}
//     size_t n = 500;
//     printf("Type\t\tSize\tMemory\tInsert\tFind\tComp\n");
//     printf("Bin Tree\t");
//     getBinTreeData(n);
//     printf("AVL Tree\t");
//     getAvlTreeData(n);
//     printf("Open Hash Map\t");
//     getOpenHashMapData(n);
//     printf("Closed Hash Map\t");
//     getClosedHashMapData(n);
//     n = 5000;
//     printf("\n\nType\t\tSize\tMemory\tInsert\tFind\tOperaions\n");
//     printf("Bin Tree\t");
//     getBinTreeData(n);
//     printf("AVL Tree\t");
//     getAvlTreeData(n);
//     printf("Open Hash Map\t");
//     getOpenHashMapData(n);
//     printf("Closed Hash Map\t");
//     getClosedHashMapData(n);
// }
