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
        return treeRemoveNode(head);

    return head;
}

TreeNode *treeRemoveNode(TreeNode *node)
{
    if (!node)
        return NULL;

    if (!node->left)
    {
        TreeNode *temp = node->right;
        freeNode(node);
        return temp;
    }

    if (!node->right)
    {
        TreeNode *temp = node->left;
        freeNode(node);
        return temp;
    }

    TreeNode *successor = treeGetSmallest(node->right);
    node->data = successor->data;
    node->right = treeRemove(node->right, successor->data->name);

    return node;
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
        return treeRemoveNode(head);
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

void depthFirstSearch(TreeNode *head, void (*action)(TreeNode *, void *), void *param)
{
    if (!head)
        return;
    action(head, param);
    depthFirstSearch(head->left, action, param);
    depthFirstSearch(head->right, action, param);
}

void freeNode(TreeNode *node)
{
    if (node)
        free(node);
}
