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
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *treeInsert(TreeNode *parent, TreeNode *head, StudentData *data, int *rc);

TreeNode *treeRemove(TreeNode *head, const char *name);

TreeNode *removeIfLowScore(TreeNode *head);

void depthFirstSearch(TreeNode *head, void (*action)(TreeNode *));

void freeNode(TreeNode *node);
