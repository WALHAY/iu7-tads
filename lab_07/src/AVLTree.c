#include "../inc/AVLTree.h"

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

static inline ssize_t getHeight(const AVLTreeNode *node)
{
    return node ? node->height : 0;
}

static ssize_t getBalanceFactor(const AVLTreeNode *node)
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

static void recalculateHeight(AVLTreeNode *node)
{
    if (node)
        node->height = MAX(getHeight(node->left), getHeight(node->right)) + 1;
}

static AVLTreeNode *treeRotateRight(AVLTreeNode *node)
{
    AVLTreeNode *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    recalculateHeight(node);
    temp->height = MAX(getHeight(temp->right), getHeight(node)) + 1;
    return temp;
}

static AVLTreeNode *treeRotateLeft(AVLTreeNode *node)
{
    AVLTreeNode *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    recalculateHeight(node);
    temp->height = MAX(getHeight(temp->left), getHeight(node)) + 1;
    return temp;
}

AVLTreeNode *avlTreeBalance(AVLTreeNode *node)
{
    ssize_t bf = getBalanceFactor(node);
    int key = node->value;

    // Left Left Case
    if (bf > 1 && key < node->left->value)
        return treeRotateRight(node);
    // Right Right Case
    if (bf < -1 && key > node->right->value)
        return treeRotateLeft(node);
    // Left Right Case
    if (bf > 1 && key > node->left->value)
    {
        node->left = treeRotateLeft(node->left);
        return treeRotateLeft(node);
    }
    // Right Left Case
    if (bf < -1 && key < node->right->value)
    {
        node->right = treeRotateRight(node->right);
        return treeRotateRight(node);
    }
    return node;
}

AVLTreeNode *avlTreeInsert(AVLTreeNode *root, int value)
{
    if (!root)
        return createAVLTreeNode(value);

    if (value < root->value)
        root->left = avlTreeInsert(root->left, value);
    else if (value > root->value)
        root->right = avlTreeInsert(root->right, value);

    recalculateHeight(root);
    return avlTreeBalance(root);
}

AVLTreeNode *avlTreeRemove(AVLTreeNode *root, int value)
{
    return value ? root : NULL;
}
