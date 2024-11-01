#include "../inc/LinkedQueue.h"

typedef struct LinkedNode LinkedNode;

struct LinkedQueue
{
    LinkedNode *front;
    LinkedNode *back;
};

struct LinkedNode
{
    LinkedNode *next;
};

LinkedQueue *createQueue(int *rc)
{
    LinkedQueue *queue = malloc(sizeof(LinkedQueue));
    if (queue)
    {
        queue->back = NULL;
        queue->front = NULL;
    }
    else
        *rc = ALLOC_ERROR;

    return queue;
}

void pop(LinkedQueue *queue, int *rc)
{
    LinkedNode *front = queue->front;
    if (front)
    {
        front = queue->front;
        free(queue->front);
        queue->front = front;
    }
    else
        *rc = EMPTY_QUEUE_POP;
}

void push(LinkedQueue *queue, int *rc)
{
    LinkedNode *node = malloc(sizeof(LinkedNode));
    if (node)
    {
        LinkedNode *back = queue->back;
        if (back)
            back->next = node;
        queue->back = node;
    }
    else
        *rc = ALLOC_ERROR;
}

void freeQueue(LinkedQueue *queue)
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
