#include "../inc/ArrayStack.h"
#include "../inc/LinkedStack.h"
#include <stdbool.h>
#include <stdio.h>

int main(void)
{

    ArrayStack *stack = arrayStack(8);
    int i = 5;
    while (i--)
        printf("Pushed %p\n", (void *)push_arr(stack, i + 1));

    printf("\n");
    i = 5;
    while (i--)
        printf("Popped %p\n", (void *)pop_arr(stack));
    return 0;
}
