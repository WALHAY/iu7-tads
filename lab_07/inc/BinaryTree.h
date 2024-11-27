#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;

struct TreeNode
{
    int value;

    TreeNode *left;
    TreeNode *right;
};

TreeNode *treeInsert(TreeNode *root, int value);

TreeNode *treeRemove(TreeNode *root, int value);

TreeNode *treeFind(TreeNode *root, int value);

void treeDFS(TreeNode *node, void (*action)(TreeNode *, void *), void *param);
