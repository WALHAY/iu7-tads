#include "../inc/BinaryTree.h"

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

    int comparison = compareInt(value, root->value);
    if (!comparison)
        return root;

    if (comparison < 0)
        root->left = treeInsert(root->left, value);
    else
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

    int comparison = compareInt(value, root->value);
    if (comparison < 0)
        root->left = treeRemove(root->left, value);
    else if (comparison > 0)
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

    int comparison = compareInt(value, root->value);
    if (comparison == 0)
        return root;
    else if (comparison < 0)
        return treeFind(root->left, value);
    else
        return treeFind(root->right, value);

    return NULL;
}
