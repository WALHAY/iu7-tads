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

    int height;
};

int getCompAmountAvl(void);

void clearCompAvl(void);

AVLTreeNode *avlTreeInsert(AVLTreeNode *root, char *key, int value);

AVLTreeNode *avlTreeRemove(AVLTreeNode *root, char *key);

AVLTreeNode *avlTreeFind(AVLTreeNode *root, char *key);

AVLTreeNode *avlTreeBalance(AVLTreeNode *root);

void avlTreeFree(AVLTreeNode **root);
