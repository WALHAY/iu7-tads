#include "../inc/FileIO.h"

FILE *openFile(const char *filename, const char *mode)
{
    return fopen(filename, mode);
}

void closeFile(FILE **file)
{
    if (file && *file)
    {
        fclose(*file);
        *file = NULL;
    }
}

LinkedHashMap *linkedHashMapFromFile(FILE *file)
{
    LinkedHashMap *linkedHashMap = createLinkedHashMap(INITIAL_SIZE);
    char *str = NULL;
    size_t size = 0;
    size_t n = 50;
    size_t index = 0;
    while (!feof(file) && getline(&str, &size, stdin) != -1)
    {
        char index_str[n];
        snprintf(index_str, n, "%zu", index++);
        int value = atoi(str);
        linkedHashMapInsert(linkedHashMap, index_str, value);
        if (str)
            free(str);
    }
    return linkedHashMap;
}

HashMap *hashMapFromFile(FILE *file)
{

    HashMap *hashMap = createHashMap(INITIAL_SIZE);
    char *str = NULL;
    size_t size = 0;
    size_t n = 50;
    size_t index = 0;
    while (!feof(file) && getline(&str, &size, stdin) != -1)
    {
        char index_str[n];
        snprintf(index_str, n, "%zu", index++);
        int value = atoi(str);
        hashMapInsert(hashMap, str, value);
        if (str)
            free(str);
    }
    return hashMap;
}

AVLTreeNode *avlTreeFromFile(FILE *file)
{
    AVLTreeNode *avlTree = NULL;
    char *str = NULL;
    size_t size = 0;
    size_t n = 50;
    size_t index = 0;
    while (!feof(file) && getline(&str, &size, stdin) != -1)
    {
        char index_str[n];
        snprintf(index_str, n, "%zu", index++);
        int value = atoi(str);
        avlTree = avlTreeInsert(avlTree, str, value);
        if (str)
            free(str);
    }
    return avlTree;
}

TreeNode *binaryTreeFromFile(FILE *file)
{
    TreeNode *node = NULL;
    char *str = NULL;
    size_t size = 0;
    size_t n = 50;
    size_t index = 0;
    while (!feof(file) && getline(&str, &size, stdin) != -1)
    {
        char index_str[n];
        snprintf(index_str, n, "%zu", index++);
        int value = atoi(str);
        node = treeInsert(node, str, value);
        if (str)
            free(str);
    }
    return node;
}
