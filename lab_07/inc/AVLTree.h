#pragma once

#include "BinaryTree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct AVLTreeNode AVLTreeNode;

struct AVLTreeNode
{
    int value;

    AVLTreeNode *left;
    AVLTreeNode *right;

    int height;
};

int getCompAmountAvl(void);

void clearCompAvl(void);

AVLTreeNode *avlTreeInsert(AVLTreeNode *root, int value);

AVLTreeNode *avlTreeRemove(AVLTreeNode *root, int value);

AVLTreeNode *avlTreeFind(AVLTreeNode *root, int value);

AVLTreeNode *avlTreeBalance(AVLTreeNode *root);

void avlTreeFree(AVLTreeNode **root);
