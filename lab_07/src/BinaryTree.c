#include "../inc/BinaryTree.h"

static int comp = 0;

int getCompAmount(void)
{
    return comp;
}

void clearComp(void)
{
    comp = 0;
}

static TreeNode *createTreeNode(char *key, int value)
{
    TreeNode *newTreeNode = malloc(sizeof(TreeNode));
    if (newTreeNode)
    {
        newTreeNode->key = strdup(key);
        newTreeNode->value = value;
        newTreeNode->left = NULL;
        newTreeNode->right = NULL;
    }
    return newTreeNode;
}

static void freeNode(TreeNode *node)
{
    if (node)
    {
        if (node->key)
            free(node->key);
        free(node);
    }
}

TreeNode *treeInsert(TreeNode *root, char *key, int value)
{
    if (!root)
        return createTreeNode(key, value);

    int comparison = strcmp(key, root->key);
    comp++;
    if (comparison < 0)
        root->left = treeInsert(root->left, key, value);
    else if (comparison > 0)
        root->right = treeInsert(root->right, key, value);

    return root;
}

static TreeNode *treeGetSmallest(TreeNode *root)
{
    while (root && root->left)
        root = root->left;
    return root;
}

TreeNode *treeRemove(TreeNode *root, char *key)
{
    if (!root)
        return root;

    int comparison = strcmp(key, root->key);
    if (comparison < 0)
        root->left = treeRemove(root->left, key);
    else if (comparison > 0)
        root->right = treeRemove(root->right, key);
    else
    {
        if (!root->left)
        {
            TreeNode *temp = root->right;
            freeNode(root);
            return temp;
        }

        if (!root->right)
        {
            TreeNode *temp = root->left;
            freeNode(root);
            return temp;
        }

        TreeNode *successor = treeGetSmallest(root->right);
        root->key = successor->key;
        root->value = successor->value;
        root->right = treeRemove(root->right, successor->key);
    }
    return root;
}

TreeNode *treeFind(TreeNode *root, char *key)
{
    if (!root)
        return NULL;

    if (!strcmp(key, root->key))
        return root;
    else if (strcmp(key, root->key) < 0)
        return treeFind(root->left, key);
    else
        return treeFind(root->right, key);

    return NULL;
}

void treeDFS(TreeNode *node, void (*action)(TreeNode *, void *), void *param)
{
    if (!node)
        return;

    action(node, param);
    treeDFS(node->left, action, param);
    treeDFS(node->right, action, param);
}

void treeFree(TreeNode **root)
{
    if (!root || !*root)
        return;

    treeFree(&(*root)->left);
    treeFree(&(*root)->right);
    freeNode(*root);
    *root = NULL;
}
