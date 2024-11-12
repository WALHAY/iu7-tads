#include "../inc/BinaryTree.h"

TreeNode *createNode(TreeNode *parent, char *name, float score, int *rc)
{
    TreeNode *node = malloc(sizeof(TreeNode));
    if (node)
    {
        node->parent = parent;
        node->data.name = name;
        node->data.score = score;
    }
    else
        *rc = ALLOC_ERROR;
    return node;
}

TreeNode *treeInsert(TreeNode *parent, TreeNode *head, char *name, float score, int *rc)
{
    if (!head)
        return createNode(parent, name, score, rc);

    int comparison = strcmp(name, head->data.name);
    if (!comparison)
        return head;

    if (comparison < 0)
        head->left = treeInsert(head, head->left, name, score, rc);
    else
        head->right = treeInsert(head, head->right, name, score, rc);

    return head;
}

static TreeNode *treeGetSmallest(TreeNode *head)
{
    while (head && head->left)
        head = head->left;
    return head;
}

TreeNode *treeRemove(TreeNode *head, char *name, int *rc)
{
    if (!head)
        return head;

    int comparison = strcmp(name, head->data.name);
    if (comparison < 0)
        head->left = treeRemove(head->left, name, rc);
    else if (comparison > 0)
        head->right = treeRemove(head->right, name, rc);
    else
    {
        if (!head->left)
        {
            TreeNode *temp = head->right;
            freeNode(head);
            return temp;
        }

        if (!head->right)
        {
            TreeNode *temp = head->left;
            freeNode(head);
            return temp;
        }

        TreeNode *successor = treeGetSmallest(head->right);
        head->data = successor->data;
        head->right = treeRemove(head->right, successor->data.name, rc);
    }

    return head;
}

void removeLowScore(TreeNode *head)
{
}

static void copyInsert(TreeNode *node)
{
}

TreeNode *treeRebuild(TreeNode *head)
{
}

void depthFirstSearch(TreeNode *head, void (*action)(TreeNode *))
{
    if (!head)
        return;
    action(head);
    depthFirstSearch(head->left, action);
    depthFirstSearch(head->right, action);
}

void freeNode(TreeNode *node)
{
    if (node)
        free(node);
}
