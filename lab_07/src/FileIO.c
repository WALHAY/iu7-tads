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
    size_t n = 50;
    size_t index = 0;
    int value = 0;
    while (fscanf(file, "%d", &value) == 1)
    {
        char index_str[n];
        snprintf(index_str, n, "%zu", index++);
        linkedHashMapInsert(linkedHashMap, index_str, value);
    }
    return linkedHashMap;
}

HashMap *hashMapFromFile(FILE *file)
{

    HashMap *hashMap = createHashMap(INITIAL_SIZE);
    size_t n = 50;
    size_t index = 0;
    int value = 0;
    while (fscanf(file, "%d", &value) == 1)
    {
        char index_str[n];
        snprintf(index_str, n, "%zu", index++);
        hashMapInsert(hashMap, index_str, value);
    }
    return hashMap;
}

AVLTreeNode *avlTreeFromFile(FILE *file)
{
    AVLTreeNode *avlTree = NULL;
    size_t n = 50;
    size_t index = 0;
    int value = 0;
    while (fscanf(file, "%d", &value) == 1)
    {
        char index_str[n];
        snprintf(index_str, n, "%zu", index++);
        avlTree = avlTreeInsert(avlTree, index_str, value);
    }
    return avlTree;
}

TreeNode *binaryTreeFromFile(FILE *file)
{
    TreeNode *node = NULL;
    size_t n = 50;
    size_t index = 0;
    int value = 0;
    while (fscanf(file, "%d", &value) == 1)
    {
        char index_str[n];
        snprintf(index_str, n, "%zu", index++);
        node = treeInsert(node, index_str, value);
    }
    return node;
}
