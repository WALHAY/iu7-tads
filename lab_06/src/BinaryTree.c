#include "../inc/BinaryTree.h"

static TreeNode *createNode(TreeNode *parent, void *data, int *rc)
{
    TreeNode *node = malloc(sizeof(TreeNode));
    if (node)
    {
        node->parent = parent;
        node->data = data;
    }
    else
        *rc = ALLOC_ERROR;
    return node;
}

TreeNode *treeInsert(TreeNode *parent, TreeNode *head, StudentData *data, int *rc)
{
    if (!head)
        return createNode(parent, data, rc);

    int comparison = strcmp(head->data->name, data->name);
    if (!comparison)
        return head;

    if (comparison < 0)
        head->left = treeInsert(head, head->left, data, rc);
    else
        head->right = treeInsert(head, head->right, data, rc);

    return head;
}

static TreeNode *treeGetSmallest(TreeNode *head)
{
    while (head && head->left)
        head = head->left;
    return head;
}

TreeNode *removeIfLowScore(TreeNode *head)
{
    if (!head)
        return head;

    if (head->left)
        head->left = removeIfLowScore(head->left);

    if (head->right)
        head->right = removeIfLowScore(head->right);

    if (head->data->score <= 2)
    {
        if (!head->left)
        {
            TreeNode *temp = head->right;
            freeNode(head);
            return removeIfLowScore(temp);
        }

        if (!head->right)
        {
            TreeNode *temp = head->left;
            freeNode(head);
            return removeIfLowScore(temp);
        }

        TreeNode *successor = treeGetSmallest(head->right);
        head->data = successor->data;
        head->right = treeRemove(head->right, successor->data->name);
    }

    return head;
}

TreeNode *treeRemove(TreeNode *head, const char *name)
{
    if (!head)
        return head;

    int comparison = strcmp(name, head->data->name);
    if (comparison < 0)
        head->left = treeRemove(head->left, name);
    else if (comparison > 0)
        head->right = treeRemove(head->right, name);
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
        head->right = treeRemove(head->right, successor->data->name);
    }

    return head;
}

TreeNode *treeFind(TreeNode *head, const char *prefix)
{
    if (!head)
        return NULL;

    int comparison = strncmp(prefix, head->data->name, strlen(prefix));
    if (comparison == 0)
        return head;
    else if (comparison < 0)
        return treeFind(head->left, prefix);
    else
        return treeFind(head->right, prefix);

    return NULL;
}

void depthFirstSearch(TreeNode *head, void (*action)(TreeNode *))
{
    if (!head)
        return;
    depthFirstSearch(head->left, action);
    depthFirstSearch(head->right, action);
    action(head);
}

void freeNode(TreeNode *node)
{
    if (node)
        free(node);
}
