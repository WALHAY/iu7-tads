#include "../inc/Comparison.h"

#define TRIES 100

static void compareMemory(size_t elements, FILE *out)
{
    size_t linkedMemory = sizeof(LinkedStack) + sizeof(LinkedStackNode) * elements;
    size_t arrayMemory = sizeof(ArrayStack) + sizeof(uintptr_t *) * ARR_SIZE;

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
    ssize_t linked = (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / TRIES;
    destroyStack(lStack);

    ArrayStack *arrStack = arrayStack(&rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    for (size_t i = 0; i < TRIES; ++i)
        pushArr(arrStack, rand(), &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    ssize_t array = (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / TRIES;
    destroyStackArr(arrStack);

    int boost = (linked - array) * 100.0f / linked;
    fprintf(out, "%zu\t%zu\t%d%%\n", linked, array, boost);
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
    ssize_t linked = (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / TRIES;
    destroyStack(lStack);

    ArrayStack *arrStack = arrayStack(&rc);
    for (size_t i = 0; i < TRIES; ++i)
        pushArr(arrStack, rand(), &rc);

    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    for (size_t i = 0; i < TRIES; ++i)
        popArr(arrStack, &rc);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    ssize_t array = (1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec)) / TRIES;
    destroyStackArr(arrStack);

    int boost = (linked - array) * 100.0f / linked;
    fprintf(out, "%zu\t%zu\t%d%%\n", linked, array, boost);
}

void compareTaDS(FILE *out)
{
    fprintf(out, "Memory comparison (in bytes)\n");
    fprintf(out, "Array Stack is limited to %d elements\n", ARR_SIZE);
    fprintf(out, "Elements\tLinked\tArray\n");
    compareMemory(500, out);
    compareMemory(5000, out);
    compareMemory(10000, out);
    compareMemory(17000, out);

    fprintf(out, "\nPush time comparison (in nanoseconds)\n");
    fprintf(out, "Linked\tArray\tArray Boost\n");
    compareTimePush(out);

    fprintf(out, "\nPop time comparison (in nanoseconds)\n");
    fprintf(out, "Linked\tArray\tArray Boost\n");
    compareTimePop(out);
}
