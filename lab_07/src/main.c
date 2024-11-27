#include "../inc/AVLTree.h"
#include "../inc/BinaryTree.h"
#include "../inc/GraphvizIntegration.h"

static void printNode(TreeNode *node, void *param)
{
    printf("%d\n", node->value);
}

int main(void)
{
    AVLTreeNode *root = NULL;
    root = avlTreeInsert(root, 1);
    root = avlTreeInsert(root, 2);
    root = avlTreeInsert(root, 3);
    root = avlTreeInsert(root, 4);
    root = avlTreeInsert(root, 5);
    root = avlTreeInsert(root, 6);
    root = avlTreeInsert(root, 7);
    treeDFS((TreeNode *)root, printNode, NULL);
    drawGraph((TreeNode *)root, "nigga", true);
    return 0;
}
