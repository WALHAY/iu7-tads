#pragma once

#include "../inc/LinkedQueue.h"
#include "../inc/ArrayQueue.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    size_t firstMin;
    size_t firstMax;
    size_t secondMin;
    size_t secondMax;
    size_t oaFirstMin;
    size_t oaFirstMax;
    size_t oaSecondMin;
    size_t oaSecondMax;
} TimeSpecification;

void task(size_t requests, TimeSpecification *timings);

void taskArray(size_t requests, TimeSpecification *timings);
