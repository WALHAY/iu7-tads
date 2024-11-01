#pragma once

#include <stdlib.h>
#include "Defines.h"

typedef struct LinkedQueue LinkedQueue;

LinkedQueue *createQueue(int *rc);

void pop(LinkedQueue *queue, int *rc);

void push(LinkedQueue *queue, int *rc);

void freeQueue(LinkedQueue *queue);
