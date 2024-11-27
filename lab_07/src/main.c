#include "../inc/AVLTree.h"
#include "../inc/GraphvizIntegration.h"

static int compareInt(const int a, const int b)
{
    return a > b ? 1 : -(a < b);
}

int main(int argc, char **argv)
{
    Node *node = NULL;
    node = treeInsert(node, 15, compareInt);
    node = treeInsert(node, 14, compareInt);
    node = treeInsert(node, 13, compareInt);
    node = treeInsert(node, 12, compareInt);
    node = treeInsert(node, 11, compareInt);
    node = treeInsert(node, 10, compareInt);
    drawGraph(node, "llll", true);
    return 0;
}
