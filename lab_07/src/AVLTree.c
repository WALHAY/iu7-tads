#include "../inc/AVLTree.h"

static int comp = 0;

int getCompAmountAvl(void)
{
    return comp;
}

void clearCompAvl(void)
{
    comp = 0;
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static AVLTreeNode *createAVLTreeNode(int value)
{
    AVLTreeNode *newAVLTreeNode = malloc(sizeof(AVLTreeNode));
    if (newAVLTreeNode)
    {
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

AVLTreeNode *avlTreeInsert(AVLTreeNode *root, int value)
{
    if (!root)
        return createAVLTreeNode(value);

    comp++;
    if (value < root->value)
        root->left = avlTreeInsert(root->left, value);
    else if (value > root->value)
        root->right = avlTreeInsert(root->right, value);
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

AVLTreeNode *avlTreeRemove(AVLTreeNode *root, int value)
{
    if (!root)
        return root;

    if (value < root->value)
        root->left = avlTreeRemove(root->left, value);
    else if (value > root->value)
        root->right = avlTreeRemove(root->right, value);
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
        root->right = avlTreeRemove(root->right, successor->value);
    }
    if (!root)
        return root;

    return avlTreeBalance(root);
}

AVLTreeNode *avlTreeFind(AVLTreeNode *root, int value)
{
    return (AVLTreeNode *)treeFind((TreeNode *)root, value);
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
