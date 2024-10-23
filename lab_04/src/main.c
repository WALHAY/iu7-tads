#include "ArrayStack.h"
#include "LinkedStack.h"
#include "TextUserInterface.h"
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    int rc = SUCCESS;
    ArrayStack *aStack = arrayStack(&rc);
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
