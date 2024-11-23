#pragma once

#include "Defines.h"
#include "Student.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode
{
    StudentData *data;

    TreeNode *left;
    TreeNode *right;
};

TreeNode *treeInsert(TreeNode *head, StudentData *data, int *rc);

TreeNode *treeRemove(TreeNode *head, const char *name);

TreeNode *treeFind(TreeNode *head, const char *prefix);

TreeNode *removeIfLowScore(TreeNode *head);

void depthFirstSearch(TreeNode *head, void (*action)(TreeNode *, void *), void *param);

void freeNode(TreeNode *node);
