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
    node->data = node;
    return node;
}

void destroyNode(LinkedStackNode *node)
{
    if (node)
        free(node);
}

LinkedStackNode *push(LinkedStack *stack)
{
    LinkedStackNode *node = linkedStackNode();

    LinkedStackNode *head = stack->stackPointer;
    if (head)
        node->next = head;

    stack->stackPointer = node;
    return node;
}

LinkedStackNode *pop(LinkedStack *stack)
{
    LinkedStackNode *tmp = stack->stackPointer;

    stack->stackPointer = tmp->next;
    destroyNode(tmp);
    return stack->stackPointer;
}
