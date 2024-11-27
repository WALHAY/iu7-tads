#include "../inc/AVLTree.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static int getHeight(const Node *node)
{
    return node ? node->height : 0;
}

static int getBalanceFactor(const Node *node)
{
    return getHeight(node->right) - getHeight(node->left);
}

static void recalculateHeight(Node *node)
{
    node->height = MAX(getHeight(node->left), getHeight(node->right)) + 1;
}

static Node *createNode(int value)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode)
    {
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
    }
    return newNode;
}

Node *treeInsert(Node *node, int value, int (*comparator)(const int, const int))
{
    if (!node)
        return createNode(value);

    int cmp = comparator(value, node->value);
    if (!cmp)
        return node;

    if (cmp < 0)
        node->left = treeInsert(node->left, value, comparator);
    else
        node->right = treeInsert(node->right, value, comparator);

    return treeBalance(node);
}

Node *treeRemove(Node *root, int value, int (*comparator)(const int, const int))
{
    return NULL;
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

void treeBFS(Node *node, void (*action)(Node *, void *), void *param)
{
    if (!node)
        return;

    action(node, param);
    treeBFS(node->left, action, param);
    treeBFS(node->right, action, param);
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
