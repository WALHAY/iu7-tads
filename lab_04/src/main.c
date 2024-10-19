#include "../inc/ArrayStack.h"
#include "../inc/LinkedStack.h"
#include "../inc/TextUserInterface.h"
#include <stdbool.h>

int main(void)
{

    ArrayStack *aStack = arrayStack(8);
    LinkedStack *lStack = linkedStack();
    while (true)
        executeOperation(lStack, aStack);
    return 0;
}
