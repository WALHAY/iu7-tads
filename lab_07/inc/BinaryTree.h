#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode
{
    char *key;
    int value;

    TreeNode *left;
    TreeNode *right;
};

int getCompAmount(void);

void clearComp(void);

TreeNode *treeInsert(TreeNode *root, char *key, int value);

TreeNode *treeRemove(TreeNode *root, char *key);

TreeNode *treeFind(TreeNode *root, char *key);

void treeDFS(TreeNode *node, void (*action)(TreeNode *, void *), void *param);

void treeFree(TreeNode **root);
