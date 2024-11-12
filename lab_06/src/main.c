#include "../inc/BinaryTree.h"
#include "../inc/Defines.h"
#include "../inc/TextUserInterface.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    TreeNode *head = NULL;

    while (true)
        printf("%s\n", getErrorMessage(executeOperation(&head)));
    return SUCCESS;
}
