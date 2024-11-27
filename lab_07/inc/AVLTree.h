#pragma once

#include "BinaryTree.h"
#include "Utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct AVLTreeNode AVLTreeNode;

struct AVLTreeNode
{
    int value;

    AVLTreeNode *left;
    AVLTreeNode *right;

    size_t balanceFactor;
};

AVLTreeNode *avlTreeInsert(AVLTreeNode *root, int value);

AVLTreeNode *avlTreeRemove(AVLTreeNode *root, int value);

AVLTreeNode *avlTreeBalance(AVLTreeNode *root);
