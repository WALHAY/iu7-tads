#include "../inc/Statistic.h"

#define MAX(a, b) ((a > b) ? a : b)

void printMiddleData(QueueRequestsData *first, QueueRequestsData *second)
{
    printf("\nType 1 requests processed: %zu\n", first->out);
    printf("Queue\tLength\tAvg Length\n");
    printf("1\t%zu\t%.2f\n", first->currentLength, (float)first->length / first->all);
    printf("2\t%zu\t%.2f\n", second->currentLength, (float)second->length / second->all);
}

void printResultData(QueueRequestsData *first, QueueRequestsData *second, size_t requests, TimeSpecification *timings,
                     float allTime)
{

    float avgInTimeFirst = (timings->firstMin + timings->firstMax) / 2.0f;
    float avgInTimeFirstAll = avgInTimeFirst * requests;

    float avgOutTimeFirst = (timings->oaFirstMin + timings->oaFirstMax) / 2.0f;
    float avgOutTimeFirstAll = avgOutTimeFirst * requests;

    float avgInTimeSecond = (timings->secondMin + timings->secondMax) / 2.0f;

    float estimatedTime = MAX(avgInTimeFirstAll, avgOutTimeFirstAll);
    float errorEstimatedTime = fabs((allTime - estimatedTime) * 100 / estimatedTime);

    printf("\nEstimated time\tSimulation time\tError\n");
    printf("%.2f\t\t%.2f\t\t%.2f%%\n", estimatedTime, allTime, errorEstimatedTime);

    printf("\nQueue Requests\tIn\tOut\tAvg expected\n");
    printf("1\t\t%zu\t%zu\t%.2f\n", first->in, first->out, avgInTimeFirst);
    printf("2\t\t%zu\t%zu\t%.2f\n", second->in, second->out, avgInTimeSecond);

    float requestsInFirst = allTime / avgInTimeFirst;
    float errorRequestsInFirst = fabs((first->in - requestsInFirst) * 100 / requestsInFirst);

    float requestsInSecond = allTime / avgInTimeSecond;
    float errorRequestsInSecond = fabs((second->in - requestsInSecond) * 100 / requestsInSecond);

    printf("\nQueue\tExpected\tRequests\tError\n");
    printf("1\t%.2f\t\t%zu\t\t%.2f%%\n", requestsInFirst, first->in, errorRequestsInFirst);
    printf("2\t%.2f\t\t%zu\t\t%.2f%%\n", requestsInSecond, second->in, errorRequestsInSecond);

    float allWorkTime = first->allTime + second->allTime;
    float waitTime = allTime - allWorkTime;

    printf("\nIdle time: %.2f\n", waitTime);
}
