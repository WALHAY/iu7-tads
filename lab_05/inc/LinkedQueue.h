#pragma once

#include <stdlib.h>
#include "Defines.h"
#include <stdbool.h>

struct LinkedQueueType;

typedef struct LinkedQueueType* LinkedQueue;

LinkedQueue createQueue(int *rc);

int pop(LinkedQueue queue, int *rc);

void push(LinkedQueue queue, int value, int *rc);

bool isEmpty(LinkedQueue queue);

void freeQueue(LinkedQueue queue);
