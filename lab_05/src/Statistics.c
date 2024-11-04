#include "../inc/Statistic.h"

#define MAX(a, b) ((a > b) ? a : b)

void printMiddleData(QueueRequestsData *first, QueueRequestsData *second)
{

    printf("Заявок 1го типа обработано = %zu\n\n", first->out);

    printf("Текущая длина очереди 1го типа = %zu\n", first->currentLength);
    printf("Средняя длина очереди 1го типа = %f\n\n", (float)(first->length) / first->all);

    printf("Текущая длина очереди 2го типа = %zu\n", second->currentLength);
    printf("Средняя длина очереди 2го типа = %f\n\n", (float)(second->length) / second->all);

    printf("---------------------------------------\n\n");
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

    printf("Общее время моделировния = %.2f"
           "\nПогрешность моделирования = %.2f%%\n",
           allTime, errorEstimatedTime);

    printf("\nЗаявок вошло в 1ую очередь = %zu"
           "\nЗаявок 1ой очереди вышло = %zu"
           "\nСреднее время обработки заявки в 1ой очереди (ожидаемое) = %.2f\n",
           first->in, first->out, avgInTimeFirst);

    printf("\nЗаявок вошло в 2ую очередь = %zu"
           "\nЗаявок 2ой очереди вышло = %zu"
           "\nСреднее время обработки заявки в 2ой очереди (ожидаемое) = %.2f\n",
           second->in, second->out, avgInTimeSecond);

    float requestsInFirst = allTime / avgInTimeFirst;
    float errorRequestsInFirst = fabs((first->in - requestsInFirst) * 100 / requestsInFirst);

    float requestsInSecond = allTime / avgInTimeSecond;
    float errorRequestsInSecond = fabs((second->in - requestsInSecond) * 100 / requestsInSecond);

    printf("\nПогрешность ввода заявок в 1ую очередь %.2f%%"
           "\nПогрешность ввода заявок во 2ую очередь %.2f%%\n",
           errorRequestsInFirst, errorRequestsInSecond);

    float allWorkTime = first->allTime + second->allTime;
    float waitTime = allTime - allWorkTime;

    printf("\nВремя простоя = %.2f\n", waitTime);
}
