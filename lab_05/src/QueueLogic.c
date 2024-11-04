#include "../inc/QueueLogic.h"

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)

typedef struct
{
    size_t in;
    size_t out;
    size_t all;
    size_t length;
    size_t currentLength;
    float all_time;
} QueueRequestsData;

static float randBetween(int min, int max)
{
    return (max - min) * (float)(rand()) / (float)RAND_MAX + min;
}

void task(size_t timeFirstMin, size_t timeFirstMax, size_t timeSecondMin, size_t timeSecondMax, size_t timeOaFirstMin,
          size_t timeOaFirstMax, size_t timeOaSecondMin, size_t timeOaSecondMax)
{
    int rc = SUCCESS;
    LinkedQueue q1 = createQueue(&rc);
    LinkedQueue q2 = createQueue(&rc);

    QueueRequestsData qData1 = {0, 0, 0, 0, 0, 0};

    QueueRequestsData qData2 = {0, 0, 0, 0, 0, 0};

    bool queueType = false; // false - 1, true = 2
    float oaTime = 0;

    float allTime = 0;

    size_t toShow = 0;

    while (qData1.out < 1000)
    {
        if (qData1.in == 0)
            qData1.in = randBetween(timeFirstMin, timeFirstMax);

        if (qData2.in == 0)
            qData2.in = randBetween(timeSecondMin, timeSecondMax);

        if (oaTime == 0)
        {
            if (!isEmpty(q1))
            {
                oaTime = randBetween(timeOaFirstMin, timeOaFirstMax);
                queueType = false;
                pop(q1, &rc);

                qData1.currentLength--;
                qData1.all++;
                qData1.length += qData1.currentLength;

                qData1.all_time += oaTime;
            }
            else if (!isEmpty(q2))
            {
                oaTime = randBetween(timeOaSecondMin, timeOaSecondMax);
                queueType = true;
                pop(q2, &rc);

                qData2.currentLength--;
                qData2.all++;
                qData2.length += qData2.currentLength;

                qData2.all_time += oaTime;
            }
        }

        float minTime = MIN(qData1.in, qData2.in);

        if (oaTime != 0)
            minTime = MIN(minTime, oaTime);

        if (oaTime == minTime)
        {
            oaTime = 0;

            if (queueType)
                qData2.out++;
            else
                qData1.out++;
        }
        else if (qData1.in == minTime)
        {
            push(q1, 0, &rc);

            qData1.in++;
            qData1.currentLength++;
            qData1.all++;
            qData1.length += qData1.currentLength;
        }
        else if (qData2.in == minTime)
        {
            push(q2, 1, &rc);

            qData2.in++;
            qData2.currentLength++;
            qData2.all++;
            qData2.length += qData2.currentLength;
        }

        qData1.in -= minTime;
        qData2.in -= minTime;

        if (oaTime >= minTime)
            oaTime -= minTime;

        allTime += minTime;

        // info every 100
        if (qData1.out % 100 == 0 && qData1.out != toShow)
        {
            toShow = qData1.out;
            printf("Заявок 1го типа обработано = %zu\n\n", qData1.out);

            printf("Текущая длина очереди 1го типа = %zu\n", qData1.currentLength);
            printf("Средняя длина очереди 1го типа = %f\n\n", (float)(qData1.length) / qData1.all);

            printf("Текущая длина очереди 2го типа = %zu\n", qData2.currentLength);
            printf("Средняя длина очереди 2го типа = %f\n\n", (float)(qData2.length) / qData2.all);
        }
    }

    float avg_q1_in = (timeFirstMin + timeFirstMax) / 2.0f;
    float all_avg_q1_in = avg_q1_in * 1000;

    float avg_q1_out = (timeOaFirstMin + timeOaFirstMax) / 2.0f;
    float all_avg_q1_out = avg_q1_out * 1000;

    float avg_q2_in = (timeSecondMin + timeSecondMax) / 2.0f;

    float estimate_model_time = MAX(all_avg_q1_in, all_avg_q1_out);

    float oaPercent = fabs((allTime - estimate_model_time) * 100 / estimate_model_time);

    printf("\n\nОбщее время моделировния = %f \
    \nПогрешность моделирования = %f\n\n",
           allTime, oaPercent);

    printf("\nЗаявок вошло в 1ую очередь = %zu \
    \nЗаявок 1ой очереди вышло = %zu \
    \nСреднее время обработки заявки в 1ой очереди (ожидаемое) = %f\n\n",
           qData1.in, qData1.out, avg_q1_in);

    printf("\nЗаявок вошло в 2ую очередь = %zu \
    \nЗаявок 2ой очереди вышло = %zu \
    \nСреднее время обработки заявки в 2ой очереди (ожидаемое) = %f\n\n",
           qData2.in, qData2.out, avg_q2_in);

    float q_in1 = allTime / avg_q1_in;
    float percent_time_in1 = fabs((qData1.in - q_in1) * 100 / q_in1);

    float q_in2 = allTime / avg_q2_in;
    float percent_time_in2 = fabs((qData2.in - q_in2) * 100 / q_in2);

    printf("Погрешность ввода заявок в 1ую очередь %f процентов \
    \nПогрешность ввода заявок во 2ую очередь %f процентов\n\n",
           percent_time_in1, percent_time_in2);

    float all_estimate_work = qData1.all_time + qData2.all_time;
    float time_wait = allTime - all_estimate_work;

    printf("\nВремя простоя = %f\n\n", fabs(time_wait));
}
