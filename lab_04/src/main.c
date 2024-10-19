#include "../inc/ArrayStack.h"
#include "../inc/LinkedStack.h"
#include "../inc/TextUserInterface.h"
#include <stdbool.h>

int main(void)
{

    int rc = SUCCESS;
    ArrayStack *aStack = arrayStack(8, &rc);
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
