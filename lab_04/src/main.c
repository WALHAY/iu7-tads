#include "../inc/LinkedStack.h"
#include <stdbool.h>
#include <stdio.h>

int main(void)
{

    LinkedStack *stack = linkedStack();
    int i = 5;
    while (i--)
        printf("Pushed %p\n", (void *)push(stack));

    i = 5;
    while (i--)
        printf("Popped %p\n", (void *)pop(stack));
    return 0;
}
