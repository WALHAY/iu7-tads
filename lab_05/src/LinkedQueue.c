#include "../inc/LinkedQueue.h"

typedef struct LinkedNode LinkedNode;

struct LinkedQueueType
{
    LinkedNode *front;
    LinkedNode *back;
};

struct LinkedNode
{
    LinkedNode *next;
    int value;
};

LinkedQueue createQueue(int *rc)
{
    LinkedQueue queue = malloc(sizeof(struct LinkedQueueType));
    if (queue)
    {
        queue->back = NULL;
        queue->front = NULL;
    }
    else
        *rc = ALLOC_ERROR;

    return queue;
}

int pop(LinkedQueue queue, int *rc)
{
    if (isEmpty(queue))
    {
        *rc = EMPTY_QUEUE_POP;
        return 0;
    }

    LinkedNode *temp = queue->front;
    queue->front = queue->front->next;
    int value = temp->value;
    free(temp);
    return value;
}

void push(LinkedQueue queue, int value, int *rc)
{
    LinkedNode *node = malloc(sizeof(LinkedNode));
    if (!node)
    {
        *rc = ALLOC_ERROR;
        return;
    }

    node->value = value;
    if (isEmpty(queue))
    {
        queue->front = queue->back = node;
        return;
    }

    queue->back->next = node;
    queue->back = node;
}

bool isEmpty(LinkedQueue queue)
{
    return queue->front == NULL;
}

void freeQueue(LinkedQueue queue)
{
    if (queue)
    {
        LinkedNode *node = queue->front;
        while (node)
        {
            LinkedNode *next_node = node->next;
            free(node);
            node = next_node;
        }
        free(queue);
    }
}
