#include "../inc/ArrayQueue.h"
#include <stdio.h>

#define SIZE 4

struct ArrayQueueType
{
    int data[SIZE];
    int front;
    int back;
};

static void shiftArrayQueue(ArrayQueue queue, size_t offset)
{
    offset += 1;
    memmove(queue->data, queue->data + offset, sizeof(int) * (queue->back - queue->front - 1));
    queue->front -= offset;
    queue->back -= offset;
}

ArrayQueue createArrayQueue(int *rc)
{
    ArrayQueue queue = malloc(sizeof(struct ArrayQueueType));

    if (queue)
    {
        queue->front = -1;
        queue->back = 0;
    }
    else
        *rc = ALLOC_ERROR;

    return queue;
}

void pushArr(ArrayQueue queue, int value, int *rc)
{
    if (isFullArr(queue))
    {
        if (queue->front >= 0)
            shiftArrayQueue(queue, queue->front);
        else
        {
            *rc = PUSH_FULL_ARR_QUEUE;
            return;
        }
    }

    queue->data[queue->back++] = value;
}

int popArr(ArrayQueue queue, int *rc)
{
    if (isEmptyArr(queue))
    {
        *rc = EMPTY_QUEUE_POP;
        return 0;
    }
    return queue->data[++queue->front];
}

bool isEmptyArr(ArrayQueue queue)
{
    return queue->front == queue->back - 1;
}

bool isFullArr(ArrayQueue queue)
{
    return queue->back == SIZE;
}

void freeArrayQueue(ArrayQueue queue);
