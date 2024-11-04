#include "../inc/Comparison.h"

#define TRIES 5000

static void compareMemory(size_t elements, FILE *out)
{
    size_t linkedMemory = sizeofQueue() + sizeofNode() * elements;
    size_t arrayMemory = sizeofArrayQueue() + sizeof(uintptr_t *) * SIZE;

    fprintf(out, "%zu\t\t%zu\t%zu\n", elements, linkedMemory, arrayMemory);
}

static void compareTimePush(FILE *out)
{
    int rc = SUCCESS;

    struct timespec t1, t2;

    ssize_t linked = 0, array = 0;

    LinkedQueue linkedQueue = createQueue(&rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    for (size_t i = 0; i < TRIES; ++i)
        push(linkedQueue, 0, &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    linked += (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec));
    freeQueue(linkedQueue);

    rc = SUCCESS;

    ArrayQueue arrayQueue = createArrayQueue(&rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    for (size_t i = 0; i < TRIES; ++i)
        pushArr(arrayQueue, 0, &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    array += (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec));
    freeArrayQueue(arrayQueue);

    int boost = (linked - array) * 100.0f / linked;
    fprintf(out, "%zu\t%zu\t%d%%\n", linked, array, boost);
}

static void compareTimePop(FILE *out)
{
    int rc = SUCCESS;

    struct timespec t1, t2;

    ssize_t linked = 0, array = 0;

    LinkedQueue linkedQueue = createQueue(&rc);
    for (size_t i = 0; i < TRIES; ++i)
        push(linkedQueue, 0, &rc);

    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    for (size_t i = 0; i < TRIES; ++i)
        pop(linkedQueue, &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    linked += (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec));
    freeQueue(linkedQueue);

    ArrayQueue arrayQueue = createArrayQueue(&rc);
    for (size_t i = 0; i < TRIES; ++i)
        pushArr(arrayQueue, 0, &rc);

    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    for (size_t i = 0; i < TRIES; ++i)
        popArr(arrayQueue, &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    array += (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec));
    freeArrayQueue(arrayQueue);

    int boost = (linked - array) * 100.0f / linked;
    fprintf(out, "%zu\t%zu\t%d%%\n", linked, array, boost);
}

void compareTaDS(FILE *out)
{
    fprintf(out, "Memory comparison (in bytes)\n");
    fprintf(out, "Array Queue is limited to %d elements\n", 5000);
    fprintf(out, "Elements\tLinked\tArray\n");
    compareMemory(500, out);
    compareMemory(5000, out);
    compareMemory(10000, out);

    fprintf(out, "\nPush time comparison (in nanoseconds)\n");
    fprintf(out, "Linked\tArray\tArray Boost\n");
    compareTimePush(out);

    fprintf(out, "\nPop time comparison (in nanoseconds)\n");
    fprintf(out, "Linked\tArray\tArray Boost\n");
    compareTimePop(out);
}
