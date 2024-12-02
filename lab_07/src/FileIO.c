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
    while (!feof(file) && getline(&str, &size, stdin) != -1)
    {
        int value = atoi(str);
        linkedHashMapInsert(linkedHashMap, str, value);
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
    while (!feof(file) && getline(&str, &size, stdin) != -1)
    {
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
    while (!feof(file) && getline(&str, &size, stdin) != -1)
    {
        int value = atoi(str);
        avlTree = avlTreeInsert(avlTree, str, value);
        if (str)
            free(str);
    }
    return avlTree;
}

TreeNode *binaryTreeFromFile(FILE *file);
