#pragma once

#include "../inc/LinkedQueue.h"
#include "../inc/ArrayQueue.h"
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

void task(size_t requests, TimeSpecification *timings);

void taskArray(size_t requests, TimeSpecification *timings);
