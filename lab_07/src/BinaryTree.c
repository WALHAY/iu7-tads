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

static TreeNode *createTreeNode(int value)
{
    TreeNode *newTreeNode = malloc(sizeof(TreeNode));
    if (newTreeNode)
    {
        newTreeNode->value = value;
        newTreeNode->left = NULL;
        newTreeNode->right = NULL;
    }
    return newTreeNode;
}

static void freeNode(TreeNode *node)
{
    if (node)
        free(node);
}

TreeNode *treeInsert(TreeNode *root, int value)
{
    if (!root)
        return createTreeNode(value);

    comp++;
    if (value < root->value)
        root->left = treeInsert(root->left, value);
    else if (value > root->value)
        root->right = treeInsert(root->right, value);

    return root;
}

static TreeNode *treeGetSmallest(TreeNode *root)
{
    while (root && root->left)
        root = root->left;
    return root;
}

TreeNode *treeRemove(TreeNode *root, int value)
{
    if (!root)
        return root;

    if (value < root->value)
        root->left = treeRemove(root->left, value);
    else if (value > root->value)
        root->right = treeRemove(root->right, value);
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
        root->value = successor->value;
        root->right = treeRemove(root->right, successor->value);
    }
    return root;
}

TreeNode *treeFind(TreeNode *root, int value)
{
    if (!root)
        return NULL;

    comp++;
    if (value == root->value)
        return root;
    else if (value < root->value)
        return treeFind(root->left, value);
    else
        return treeFind(root->right, value);

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
