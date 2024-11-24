#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Node Node;

struct Node
{
    int value;
    size_t height;

    Node *left;
    Node *right;
};

Node *treeInsert(Node *root, int value, int (*comparator)(const int, const int));

Node *treeRemove(Node *root, int value, int (*comparator)(const int, const int));

void depthFirstSearch(Node *node, void (*action)(Node *, void *), void *param);

Node *treeBalance(Node *root);

Node *treeRotateLeft(Node *node);

Node *treeRotateRight(Node *node);
