#include "Comparison.h"

#define TRIES 10000

static void compareMemory(size_t elements, FILE *out)
{
    int arrElements = 8 * pow(2, (int)ceil(log2(elements / 8.0)));
    size_t linkedMemory = sizeof(LinkedStack) + sizeof(LinkedStackNode) * elements;
    size_t arrayMemory = sizeof(ArrayStack) + sizeof(uintptr_t *) * arrElements;

    fprintf(out, "%zu\t\t%zu\t%zu\n", elements, linkedMemory, arrayMemory);
}

static void compareTimePush(FILE *out)
{
    int rc = SUCCESS;

    struct timespec t1, t2;

    LinkedStack *lStack = linkedStack(&rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    for (size_t i = 0; i < TRIES; ++i)
        push(lStack, &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    size_t linked = (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / TRIES;
    destroyStack(lStack);

    ArrayStack *arrStack = arrayStack(TRIES, &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    for (size_t i = 0; i < TRIES; ++i)
        pushArr(arrStack, rand(), &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    size_t array = (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / TRIES;
    destroyStackArr(arrStack);

    fprintf(out, "%zu\t%zu\n", linked, array);
}

static void compareTimePop(FILE *out)
{
    int rc = SUCCESS;

    struct timespec t1, t2;

    LinkedStack *lStack = linkedStack(&rc);
    for (size_t i = 0; i < TRIES; ++i)
        push(lStack, &rc);

    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    for (size_t i = 0; i < TRIES; ++i)
        pop(lStack, &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    size_t linked = (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / TRIES;
    destroyStack(lStack);

    ArrayStack *arrStack = arrayStack(TRIES, &rc);
    for (size_t i = 0; i < TRIES; ++i)
        pushArr(arrStack, rand(), &rc);

    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    for (size_t i = 0; i < TRIES; ++i)
        popArr(arrStack, &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    size_t array = (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / TRIES;
    destroyStackArr(arrStack);

    fprintf(out, "%zu\t%zu\n", linked, array);
}

void compareTaDS(FILE *out)
{
    fprintf(out, "Memory comparison (in bytes)\n");
    fprintf(out, "Elements\tLinked\tArray\n");
    compareMemory(500, out);
    compareMemory(5000, out);
    compareMemory(10000, out);
    compareMemory(17000, out);

    fprintf(out, "\nPush time comparison (in nanoseconds)\n");
    fprintf(out, "Linked\tArray\n");
    compareTimePush(out);

    fprintf(out, "\nPop time comparison (in nanoseconds)\n");
    fprintf(out, "Linked\tArray\n");
    compareTimePop(out);
}
