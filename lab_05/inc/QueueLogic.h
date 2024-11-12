#pragma once

#include "../inc/ArrayQueue.h"
#include "../inc/LinkedQueue.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    float firstMin;
    float firstMax;
    float secondMin;
    float secondMax;
    float oaFirstMin;
    float oaFirstMax;
    float oaSecondMin;
    float oaSecondMax;
} TimeSpecification;

int task(size_t requests, TimeSpecification *timings, size_t *maxQueue);

int taskArray(size_t requests, TimeSpecification *timings, size_t *maxQueue);
