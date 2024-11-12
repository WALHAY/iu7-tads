#include "../inc/BinaryTree.h"
#include "../inc/Defines.h"
#include <stdio.h>
#include <stdlib.h>

void printNode(TreeNode *node)
{
    struct StudentData data = node->data;
    printf("%s %f\n", data.name, data.score);
}

int main(void)
{
    int rc = SUCCESS;
    TreeNode *head = NULL;

    head = treeInsert(NULL, head, "Hello", 1, &rc);
    head = treeInsert(NULL, head, "Nigger", 3, &rc);
    head = treeInsert(NULL, head, "Abc", 5, &rc);
    depthFirstSearch(head, printNode);
    return rc;
}
