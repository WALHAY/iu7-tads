#include "ArrayStack.h"
#include "LinkedStack.h"
#include "TextUserInterface.h"
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    compareTaDS(fopen("data.txt", "w"));
    int rc = SUCCESS;
    ArrayStack *aStack = arrayStack(INITIAL_SIZE, &rc);
    LinkedStack *lStack = linkedStack(&rc);
    if (rc)
    {
        printf("%s\n", getErrorMessage(rc));
        return rc;
    }

    while (true)
    {
        rc = executeOperation(lStack, aStack);
        if (rc)
            printf("%s\n", getErrorMessage(rc));
    }
    return 0;
}
