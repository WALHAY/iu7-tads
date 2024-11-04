#pragma once

#include "Defines.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

struct ArrayQueueType;

typedef struct ArrayQueueType *ArrayQueue;

ArrayQueue createArrayQueue(int *rc);

void pushArr(ArrayQueue queue, int value, int *rc);

int popArr(ArrayQueue queue, int *rc);

bool isEmptyArr(ArrayQueue queue);

bool isFullArr(ArrayQueue queue);

void freeArrayQueue(ArrayQueue queue);
