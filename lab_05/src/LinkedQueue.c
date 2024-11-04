#include "../inc/LinkedQueue.h"

typedef struct LinkedQueueNode LinkedQueueNode;

struct LinkedQueueType
{
    LinkedQueueNode *front;
    LinkedQueueNode *back;
};

struct LinkedQueueNode
{
    LinkedQueueNode *next;
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

    LinkedQueueNode *temp = queue->front;
    queue->front = queue->front->next;
    int value = temp->value;
    free(temp);
    return value;
}

void push(LinkedQueue queue, int value, int *rc)
{
    LinkedQueueNode *node = malloc(sizeof(LinkedQueueNode));
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
        LinkedQueueNode *node = queue->front;
        while (node)
        {
            LinkedQueueNode *next_node = node->next;
            free(node);
            node = next_node;
        }
        free(queue);
    }
}

inline size_t sizeofQueue(void)
{
    return sizeof(struct LinkedQueueType);
}

inline size_t sizeofNode(void)
{
    return sizeof(struct LinkedQueueNode);
}
