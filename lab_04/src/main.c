// Элементами стека являются адреса памяти.
// При реализации массивами - их вводить, при
// реализации списком – брать адрес выделенной
// памяти под элемент
#include "../inc/ArrayStack.h"
#include "../inc/LinkedStack.h"
#include "../inc/TextUserInterface.h"
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
