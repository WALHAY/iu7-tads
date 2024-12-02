#include "../inc/AVLTree.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static AVLTreeNode *createAVLTreeNode(char *key, int value)
{
    AVLTreeNode *newAVLTreeNode = malloc(sizeof(AVLTreeNode));
    if (newAVLTreeNode)
    {
        newAVLTreeNode->key = strdup(key);
        newAVLTreeNode->value = value;
        newAVLTreeNode->left = NULL;
        newAVLTreeNode->right = NULL;
        newAVLTreeNode->height = 1;
    }
    return newAVLTreeNode;
}

static void freeNode(AVLTreeNode *node)
{
    if (node)
        free(node);
}

static inline int getHeight(const AVLTreeNode *node)
{
    return node ? node->height : 0;
}

static int getBalanceFactor(const AVLTreeNode *node)
{
    return node ? getHeight(node->right) - getHeight(node->left) : 0;
}

static void recalculateHeight(AVLTreeNode *node)
{
    if (node)
        node->height = MAX(getHeight(node->right), getHeight(node->left)) + 1;
}

static AVLTreeNode *treeRotateRight(AVLTreeNode *node)
{
    AVLTreeNode *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    recalculateHeight(node);
    recalculateHeight(temp);
    return temp;
}

static AVLTreeNode *treeRotateLeft(AVLTreeNode *node)
{
    AVLTreeNode *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    recalculateHeight(node);
    recalculateHeight(temp);
    return temp;
}

AVLTreeNode *avlTreeBalance(AVLTreeNode *node)
{
    recalculateHeight(node);
    if (getBalanceFactor(node) >= 2)
    {
        if (getBalanceFactor(node->right) < 0)
            node->right = treeRotateRight(node->right);

        return treeRotateLeft(node);
    }

    if (getBalanceFactor(node) <= -2)
    {
        if (getBalanceFactor(node->left) > 0)
            node->left = treeRotateLeft(node->left);

        return treeRotateRight(node);
    }

    return node;
}

AVLTreeNode *avlTreeInsert(AVLTreeNode *root, char *key, int value)
{
    if (!key || *key == 0)
        return root;

    if (!root)
        return createAVLTreeNode(key, value);

    if (strcmp(key, root->key) < 0)
        root->left = avlTreeInsert(root->left, key, value);
    else if (strcmp(key, root->key) > 0)
        root->right = avlTreeInsert(root->right, key, value);
    else
        return root;

    if (!root)
        return root;

    return avlTreeBalance(root);
}

static AVLTreeNode *treeGetSmallest(AVLTreeNode *root)
{
    while (root && root->left)
        root = root->left;
    return root;
}

AVLTreeNode *avlTreeRemove(AVLTreeNode *root, char *key)
{
    if (!root)
        return root;

    if (strcmp(key, root->key) < 0)
        root->left = avlTreeRemove(root->left, key);
    else if (strcmp(key, root->key) > 0)
        root->right = avlTreeRemove(root->right, key);
    else
    {
        if (!root->left)
        {
            AVLTreeNode *temp = root->right;
            freeNode(root);
            return temp;
        }

        if (!root->right)
        {
            AVLTreeNode *temp = root->left;
            freeNode(root);
            return temp;
        }

        AVLTreeNode *successor = treeGetSmallest(root->right);
        root->value = successor->value;
        root->right = avlTreeRemove(root->right, successor->key);
    }

    return avlTreeBalance(root);
}

AVLTreeNode *avlTreeFind(AVLTreeNode *root, char *key)
{
    return (AVLTreeNode *)treeFind((TreeNode *)root, key);
}

void avlTreeFree(AVLTreeNode **root)
{
    if (!root || !*root)
        return;

    avlTreeFree(&(*root)->left);
    avlTreeFree(&(*root)->right);
    freeNode(*root);
    *root = NULL;
}
