#include "../inc/QueueLogic.h"
#include "../inc/Statistic.h"

#define MIN(a, b) ((a < b) ? a : b)

static float randBetween(float min, float max)
{
    return (max - min) * (float)rand() / (float)RAND_MAX + min;
}

void task(size_t requests, TimeSpecification *timings)
{
    int rc = SUCCESS;
    LinkedQueue q1 = createQueue(&rc);
    LinkedQueue q2 = createQueue(&rc);

    // данные по первым типам заявок
    QueueRequestsData qData1 = {0, 0, 0, 0, 0, 0};
    float reqTimeIn1 = 0;
    // данные по вторым типам заявок
    QueueRequestsData qData2 = {0, 0, 0, 0, 0, 0};
    float reqTimeIn2 = 0;

    bool queueType = false; // false - 1, true - 2
    // текущее время работы автомата
    float oaTime = 0;
    // общее время работы
    float allTime = 0;
    // запоминает промежуточные выводы данных
    size_t showed = 0;

    while (qData1.out < requests)
    {
        // добавление заявок в очередь
        if (reqTimeIn1 == 0)
            reqTimeIn1 = randBetween(timings->firstMin, timings->firstMax);

        if (reqTimeIn2 == 0)
            reqTimeIn2 = randBetween(timings->secondMin, timings->secondMax);

        // относительный приоритет первой очереди над второй
        if (oaTime == 0)
        {
            if (!isEmpty(q1))
            {
                oaTime = randBetween(timings->oaFirstMin, timings->oaFirstMax);
                queueType = false;
                pop(q1, &rc);

                qData1.all++;
                qData1.length += --qData1.currentLength;

                qData1.allTime += oaTime;
            }
            else if (!isEmpty(q2))
            {
                oaTime = randBetween(timings->oaSecondMin, timings->oaSecondMax);
                queueType = true;
                pop(q2, &rc);

                qData2.all++;
                qData2.length += --qData2.currentLength;

                qData2.allTime += oaTime;
            }
        }

        float minTime = MIN(reqTimeIn1, reqTimeIn2);

        if (oaTime != 0)
            minTime = MIN(minTime, oaTime);

        // самое быстрое действие - обработка заявки
        if (oaTime != 0 && oaTime == minTime)
        {
            oaTime = 0;

            if (queueType)
                qData2.out++;
            else
                qData1.out++;
        }
        // самое быстрое действие - добавление заявки 1 типа
        else if (reqTimeIn1 == minTime)
        {
            push(q1, 1, &rc);

            qData1.in++;
            qData1.currentLength++;
            qData1.all++;
            qData1.length += qData1.currentLength;
        }
        // самое быстрое действие - добавление заявки 2 типа
        else if (reqTimeIn2 == minTime)
        {
            push(q2, 2, &rc);

            qData2.in++;
            qData2.currentLength++;
            qData2.all++;
            qData2.length += qData2.currentLength;
        }

        reqTimeIn1 -= minTime;
        reqTimeIn2 -= minTime;

        if (oaTime >= minTime)
            oaTime -= minTime;

        allTime += minTime;

        if (qData1.out % 100 == 0 && qData1.out != showed)
        {
            showed = qData1.out;
            printMiddleData(&qData1, &qData2);
        }
    }
    printResultData(&qData1, &qData2, requests, timings, allTime);
}

void taskArray(size_t requests, TimeSpecification *timings)
{
    int rc = SUCCESS;
    ArrayQueue q1 = createArrayQueue(&rc);
    ArrayQueue q2 = createArrayQueue(&rc);

    // данные по первым типам заявок
    QueueRequestsData qData1 = {0, 0, 0, 0, 0, 0};
    float reqTimeIn1 = 0;
    // данные по вторым типам заявок
    QueueRequestsData qData2 = {0, 0, 0, 0, 0, 0};
    float reqTimeIn2 = 0;

    bool queueType = false; // false - 1, true - 2
    // текущее время работы автомата
    float oaTime = 0;
    // общее время работы
    float allTime = 0;
    // запоминает промежуточные выводы данных
    size_t showed = 0;

    while (qData1.out < requests)
    {
        // добавление заявок в очередь
        if (reqTimeIn1 == 0)
            reqTimeIn1 = randBetween(timings->firstMin, timings->firstMax);

        if (reqTimeIn2 == 0)
            reqTimeIn2 = randBetween(timings->secondMin, timings->secondMax);

        // относительный приоритет первой очереди над второй
        if (oaTime == 0)
        {
            if (!isEmptyArr(q1))
            {
                oaTime = randBetween(timings->oaFirstMin, timings->oaFirstMax);
                queueType = false;
                popArr(q1, &rc);

                qData1.all++;
                qData1.length += --qData1.currentLength;

                qData1.allTime += oaTime;
            }
            else if (!isEmptyArr(q2))
            {
                oaTime = randBetween(timings->oaSecondMin, timings->oaSecondMax);
                queueType = true;
                popArr(q2, &rc);

                qData2.all++;
                qData2.length += --qData2.currentLength;

                qData2.allTime += oaTime;
            }
        }

        float minTime = MIN(reqTimeIn1, reqTimeIn2);

        if (oaTime != 0)
            minTime = MIN(minTime, oaTime);

        // самое быстрое действие - обработка заявки
        if (oaTime != 0 && oaTime == minTime)
        {
            oaTime = 0;

            if (queueType)
                qData2.out++;
            else
                qData1.out++;
        }
        // самое быстрое действие - добавление заявки 1 типа
        else if (reqTimeIn1 == minTime)
        {
            pushArr(q1, 1, &rc);

            qData1.in++;
            qData1.currentLength++;
            qData1.all++;
            qData1.length += qData1.currentLength;
        }
        // самое быстрое действие - добавление заявки 2 типа
        else if (reqTimeIn2 == minTime)
        {
            pushArr(q2, 2, &rc);

            qData2.in++;
            qData2.currentLength++;
            qData2.all++;
            qData2.length += qData2.currentLength;
        }

        reqTimeIn1 -= minTime;
        reqTimeIn2 -= minTime;

        if (oaTime >= minTime)
            oaTime -= minTime;

        allTime += minTime;

        if (qData1.out % 100 == 0 && qData1.out != showed)
        {
            showed = qData1.out;
            printMiddleData(&qData1, &qData2);
        }
    }
    printResultData(&qData1, &qData2, requests, timings, allTime);
}
