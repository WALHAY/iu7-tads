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
    if (!file)
        return NULL;
    rewind(file);
    LinkedHashMap *linkedHashMap = createLinkedHashMap(INITIAL_SIZE);
    int value = 0;
    while (fscanf(file, "%d", &value) == 1)
        linkedHashMapInsert(linkedHashMap, value);
    return linkedHashMap;
}

HashMap *hashMapFromFile(FILE *file)
{
    if (!file)
        return NULL;
    rewind(file);
    HashMap *hashMap = createHashMap(INITIAL_SIZE);
    int value = 0;
    while (fscanf(file, "%d", &value) == 1)
        hashMapInsert(hashMap, value);
    return hashMap;
}

AVLTreeNode *avlTreeFromFile(FILE *file)
{
    if (!file)
        return NULL;
    rewind(file);
    AVLTreeNode *avlTree = NULL;
    int value = 0;
    while (fscanf(file, "%d", &value) == 1)
        avlTree = avlTreeInsert(avlTree, value);
    return avlTree;
}

TreeNode *binaryTreeFromFile(FILE *file)
{
    if (!file)
        return NULL;
    rewind(file);
    TreeNode *node = NULL;
    int value = 0;
    while (fscanf(file, "%d", &value) == 1)
        node = treeInsert(node, value);
    return node;
}
