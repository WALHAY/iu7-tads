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
        newAVLTreeNode->balanceFactor = 0;
    }
    return newAVLTreeNode;
}

static AVLTreeNode *treeRotateLeft(AVLTreeNode *node)
{
    AVLTreeNode *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

static AVLTreeNode *treeRotateRight(AVLTreeNode *node)
{
    AVLTreeNode *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

AVLTreeNode *avlTreeInsert(AVLTreeNode *node, int value)
{
    return avlTreeBalance((AVLTreeNode *)treeInsert((TreeNode *)node, value));
}

AVLTreeNode *avlTreeRemove(AVLTreeNode *root, int value)
{
    return avlTreeBalance((AVLTreeNode *)treeRemove((TreeNode *)root, value));
}

AVLTreeNode *avlTreeBalance(AVLTreeNode *node)
{
    return node;
}
