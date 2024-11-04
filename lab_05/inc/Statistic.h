#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "../inc/QueueLogic.h"

typedef struct
{
    size_t in;
    size_t out;
    size_t all;
    size_t length;
    size_t currentLength;
    float allTime;
} QueueRequestsData;

void printMiddleData(QueueRequestsData *first, QueueRequestsData *second);

void printResultData(QueueRequestsData *first, QueueRequestsData *second, size_t requests, TimeSpecification *timings, float allTime);
