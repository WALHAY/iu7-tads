#include "../inc/AVLTree.h"

#define MAX(a, b) ((a > b) ? (a) : (b))

static size_t getHeight(const Node *node)
{
    return node ? node->height : 0;
}

static ssize_t getBalanceFactor(const Node *node)
{
    return (ssize_t)getHeight(node->left) - getHeight(node->right);
}

static size_t recalculateHeight(Node *node)
{
    return (getHeight(node->left), getHeight(node->right));
}

static Node *createNode(int value)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode)
    {
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

Node *treeInsert(Node *node, int value, int (*comparator)(const int, const int))
{
    if (!node)
        return createNode(value);

    int cmp = comparator(value, node->value);
    if (cmp <)

        return NULL;
}

Node *treeRemove(Node *root, int value, int (*comparator)(const int, const int))
{
    return NULL;
}

void depthFirstSearch(Node *node, void (*action)(Node *, void *), void *param)
{

    if (!node)
        return;

    action(node, param);
    depthFirstSearch(node->left, action, param);
    depthFirstSearch(node->right, action, param);
}

Node *treeBalance(Node *node)
{
    recalculateHeight(node);
    if (getBalanceFactor(node) == 2)
    {
        if (getBalanceFactor(node->right) < 0)
            node->right = treeRotateRight(node->right);
        return treeRotateRight(node);
    }
    if (getBalanceFactor(node) == -2)
    {
        if (getBalanceFactor(node->left) > 0)
            node->left = treeRotateLeft(node->left);
        return treeRotateLeft(node);
    }
    return node;
}

Node *treeRotateLeft(Node *node)
{
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    recalculateHeight(node);
    recalculateHeight(temp);
    return temp;
}

Node *treeRotateRight(Node *node)
{
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    recalculateHeight(node);
    recalculateHeight(temp);
    return temp;
}
