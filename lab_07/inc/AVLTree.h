#pragma once

#include "BinaryTree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct AVLTreeNode AVLTreeNode;

struct AVLTreeNode
{
    char *key;
    int value;

    AVLTreeNode *left;
    AVLTreeNode *right;

    ssize_t height;
};

AVLTreeNode *avlTreeInsert(AVLTreeNode *root, char *key, int value);

AVLTreeNode *avlTreeRemove(AVLTreeNode *root, char *key);

AVLTreeNode *avlTreeFind(AVLTreeNode *root, char *key, int *value);

AVLTreeNode *avlTreeBalance(AVLTreeNode *root);
