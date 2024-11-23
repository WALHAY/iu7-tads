#include "../inc/BinaryTree.h"

static TreeNode *createNode(void *data, int *rc)
{
    TreeNode *node = malloc(sizeof(TreeNode));
    if (node)
    {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }
    else
        *rc = ALLOC_ERROR;
    return node;
}

TreeNode *treeInsert(TreeNode *head, StudentData *data, int (*comparator)(const StudentData *data, const StudentData *),
                     int *rc)
{
    if (!head)
        return createNode(data, rc);

    int comparison = comparator(data, head->data);
    if (!comparison)
        return head;

    if (comparison < 0)
        head->left = treeInsert(head->left, data, comparator, rc);
    else
        head->right = treeInsert(head->right, data, comparator, rc);

    return head;
}

static TreeNode *treeGetSmallest(TreeNode *head)
{
    while (head && head->left)
        head = head->left;
    return head;
}

static TreeNode *treeRemoveNode(TreeNode *node)
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
    node->right = treeRemoveNode(successor);

    return node;
}

TreeNode *filterTree(TreeNode *head, bool (*filter)(const TreeNode *node))
{
    if (!head)
        return head;

    if (head->left)
        head->left = filterTree(head->left, filter);

    if (head->right)
        head->right = filterTree(head->right, filter);

    if (head->data->score <= 2)
        return treeRemoveNode(head);

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

void destroyTree(TreeNode **node)
{
    if (node || *node)
    {
        TreeNode *temp = *node;
        TreeNode *left = temp->left;
        TreeNode *right = temp->right;
        freeNode(temp);
        *node = NULL;
        destroyTree(&left);
        destroyTree(&right);
    }
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
