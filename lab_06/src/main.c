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
    {
        int rc = executeOperation(&head);
        if (rc)
            printf("%s\n", getErrorMessage(rc));
    }
    return SUCCESS;
}
