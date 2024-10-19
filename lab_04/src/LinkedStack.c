#include "../inc/LinkedStack.h"

LinkedStack *linkedStack()
{
    LinkedStack *stack = malloc(sizeof(LinkedStack));
    stack->stackPointer = NULL;
    return stack;
}

void destroyStack(LinkedStack *stack)
{
    while (stack->stackPointer)
        pop(stack);
    free(stack);
}

LinkedStackNode *linkedStackNode()
{
    LinkedStackNode *node = malloc(sizeof(LinkedStackNode));
    node->data = (uintptr_t)node;
    return node;
}

void destroyNode(LinkedStackNode *node)
{
    if (node)
        free(node);
}

uintptr_t push(LinkedStack *stack)
{
    LinkedStackNode *node = linkedStackNode();

    LinkedStackNode *head = stack->stackPointer;
    if (head)
        node->next = head;

    stack->stackPointer = node;
    return node->data;
}

uintptr_t pop(LinkedStack *stack)
{
    LinkedStackNode *tmp = stack->stackPointer;

    stack->stackPointer = tmp->next;
    uintptr_t value = tmp->data;
    destroyNode(tmp);

    return value;
}
