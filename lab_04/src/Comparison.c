#include "Comparison.h"

#define TRIES 50

static void compareMemory(size_t elements, FILE *out)
{
    int arrElements = 8 * pow(2, (int)log2(elements / 8.0));
    size_t linkedMemory = sizeof(LinkedStack) + sizeof(LinkedStackNode) * elements;
    size_t arrayMemory = sizeof(ArrayStack) + sizeof(uintptr_t *) * arrElements;

    fprintf(out, "%zu\t\t%zu\t%zu\n", elements, linkedMemory, arrayMemory);
}

static void compareTimePush(size_t elements, FILE *out)
{
    int rc = SUCCESS;

    struct timespec t1, t2;

    size_t linked = 0;
    size_t array = 0;

    for (size_t k = 0; k < TRIES; ++k)
    {
        LinkedStack *lStack = linkedStack(&rc);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        for (size_t i = 0; i < elements; ++i)
            push(lStack, &rc);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        linked += (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / elements;
        destroyStack(lStack);

        ArrayStack *arrStack = arrayStack(elements, &rc);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        for (size_t i = 0; i < elements; ++i)
            pushArr(arrStack, rand(), &rc);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        array += (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / elements;
        destroyStackArr(arrStack);
    }

    linked /= TRIES;
    array /= TRIES;

    fprintf(out, "%zu\t\t%zu\t%zu\n", elements, linked, array);
}

static void compareTimePop(size_t elements, FILE *out)
{
    int rc = SUCCESS;

    struct timespec t1, t2;

    size_t linked = 0;
    size_t array = 0;

    for (size_t k = 0; k < TRIES; ++k)
    {
        LinkedStack *lStack = linkedStack(&rc);
        for (size_t i = 0; i < elements; ++i)
            push(lStack, &rc);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        for (size_t i = 0; i < elements; ++i)
            pop(lStack, &rc);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        linked += (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / elements;
        destroyStack(lStack);

        ArrayStack *arrStack = arrayStack(elements, &rc);
        for (size_t i = 0; i < elements; ++i)
            pushArr(arrStack, rand(), &rc);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        for (size_t i = 0; i < elements; ++i)
            popArr(arrStack, &rc);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        array += (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / elements;
        destroyStackArr(arrStack);
    }

    linked /= TRIES;
    array /= TRIES;

    fprintf(out, "%zu\t\t%zu\t%zu\n", elements, linked, array);
}

void compareTaDS(FILE *out)
{
    fprintf(out, "Memory comparison (in bytes)\n");
    fprintf(out, "Elements\tLinked\tArray\n");
    compareMemory(500, out);
    compareMemory(5000, out);
    compareMemory(10000, out);

    fprintf(out, "\nPush time comparison (in nanoseconds)\n");
    fprintf(out, "Elements\tLinked\tArray\n");
    compareTimePush(500, out);
    compareTimePush(5000, out);
    compareTimePush(10000, out);

    fprintf(out, "\nPop time comparison (in nanoseconds)\n");
    fprintf(out, "Elements\tLinked\tArray\n");
    compareTimePop(500, out);
    compareTimePop(5000, out);
    compareTimePop(10000, out);
}
