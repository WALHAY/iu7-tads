#include "../inc/Comparison.h"

#define TRIES 50

static void compareMemory(size_t elements, FILE *out)
{
    size_t linkedMemory = sizeof(LinkedStack) + sizeof(LinkedStackNode) * elements;
    size_t arrayMemory = sizeof(ArrayStack) + sizeof(uintptr_t *) * elements;

    fprintf(out, "Elements\tLinked\tArray\n");
    fprintf(out, "%zu\t\t%zu\t%zu\n\n", elements, linkedMemory, arrayMemory);
}

static void compareTime(size_t elements, FILE *out)
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

    fprintf(out, "Elements\tLinked\tArray\n");
    fprintf(out, "%zu\t\t%zu\t%zu\n\n", elements, linked / TRIES, array / TRIES);
}

void compareTaDS(FILE *out)
{
    fprintf(out, "Memory comparison\n");
    compareMemory(500, out);
    compareMemory(5000, out);
    compareMemory(10000, out);

    fprintf(out, "Time comparison\n");
    compareTime(500, out);
    compareTime(5000, out);
    compareTime(10000, out);
}
