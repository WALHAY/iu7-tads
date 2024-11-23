#include "../inc/BinaryTree.h"
#include "../inc/Defines.h"
#include "../inc/TextUserInterface.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    TreeNode *head = NULL;

    if (argc == 2)
    {
        int rc = SUCCESS;
        FILE *file = fopen(argv[1], "r");
        while (file && !feof(file))
        {
            char name[50];
            double score = 0;
            if (fscanf(file, "%s %lf", name, &score) != 2)
                break;

            StudentData *data = createData(name, score, &rc);
            if (!rc)
                head = treeInsert(NULL, head, data, &rc);
        }
    }

    while (true)
    {
        int rc = executeOperation(&head);
        if (rc)
            printf("%s\n", getErrorMessage(rc));
    }
    return SUCCESS;
}
