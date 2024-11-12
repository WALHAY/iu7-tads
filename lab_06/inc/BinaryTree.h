#include "Defines.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode
{
    struct StudentData
    {
        char *name;
        float score;
    } data;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *treeInsert(TreeNode *parent, TreeNode *head, char *name, float score, int *rc);

TreeNode *treeRemove(TreeNode *head, char *name, int *rc);

void depthFirstSearch(TreeNode *head, void (*action)(TreeNode *));

void freeNode(TreeNode *node);
