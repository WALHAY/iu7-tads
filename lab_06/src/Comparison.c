#include "../inc/Comparison.h"

#define TRIES 10

static void compareMemory(size_t elements, FILE *out)
{
    size_t mem = sizeof(TreeNode) * elements;
    fprintf(out, "%zu\t%zu\n", elements, mem);
}

static int studentComparator(const void *first, const void *second)
{
    const StudentData *fdata = *(StudentData **)first;
    const StudentData *sdata = *(StudentData **)second;
    return strcmp(fdata->name, sdata->name);
}

static char *randomString(int value)
{
    char string[255];

    size_t index = 0;
    while (value > 0)
    {
        string[index++] = value % 10 + 'a';
        value /= 10;
    }
    string[index] = 0;

    return strdup(string);
}

static void compareTimeBamboo(size_t elements, FILE *out)
{
    int rc = SUCCESS;
    struct timespec t1, t2;
    size_t insert = 0;
    size_t remove = 0;
    bool drawed = false;
    for (size_t i = 0; i < TRIES; ++i)
    {
        TreeNode *head = NULL;
        StudentData *arr[elements];
        for (size_t j = 0; j < elements; ++j)
        {
            int value = rand();
            arr[j] = createData(randomString(value), value, &rc);
        }

        qsort(arr, elements, sizeof(StudentData *), studentComparator);

        size_t l_insert = 0;
        for (size_t j = 0; j < elements; ++j)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            head = treeInsert(head, arr[j], &rc);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            l_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
        }

        if (!drawed)
        {
            char name[30];
            sprintf(name, "Bamboo_%zu", elements);
            drawGraph(head, name, false);
            drawed = true;
        }

        size_t current = elements;
        size_t l_remove = 0;
        for (size_t j = 0; j < elements; ++j)
        {
            size_t index = rand() % current--;
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            head = treeRemove(head, arr[index]->name);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            arr[index] = arr[current];
            l_remove += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
        }
        insert += l_insert / elements;
        remove += l_remove / elements;
    }

    if (rc)
        printf("Error occured!");

    insert /= TRIES;
    remove /= TRIES;
    fprintf(out, "%zu\t%zu\t%zu\n", elements, insert, remove);
}

static void compareTimeDense(size_t elements, FILE *out)
{
    int rc = SUCCESS;
    struct timespec t1, t2;
    size_t insert = 0;
    size_t remove = 0;
    static bool drawed = false;
    for (size_t i = 0; i < TRIES; ++i)
    {
        TreeNode *head = NULL;
        StudentData *arr[elements];
        for (size_t j = 0; j < elements; ++j)
        {
            int value = rand();
            arr[j] = createData(randomString(value), value, &rc);
        }

        qsort(arr, elements, sizeof(StudentData *), studentComparator);

        size_t l_insert = 0;
        for (size_t j = 0; j < elements; ++j)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            head = treeInsert(head, arr[j], &rc);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            l_insert += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
        }

        if (!drawed)
        {
            char name[30];
            sprintf(name, "Sorted_%zu", elements);
            drawGraph(head, name, false);
            drawed = true;
        }

        size_t current = elements;
        size_t l_remove = 0;
        for (size_t j = 0; j < elements; ++j)
        {
            size_t index = rand() % current--;
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            head = treeRemove(head, arr[index]->name);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            arr[index] = arr[current];
            l_remove += difftime(t2.tv_sec, t1.tv_sec) * 1e9 + difftime(t2.tv_nsec, t1.tv_nsec);
        }
        insert += l_insert / elements;
        remove += l_remove / elements;
    }

    insert /= TRIES;
    remove /= TRIES;
    fprintf(out, "%zu\t%zu\t%zu\n", elements, insert, remove);
}

static void compareAlgorithmTime(int requests, FILE *out)
{
}

void compareTaDS(FILE *out)
{
    printf("Required memory for BST depending on its size\n");
    printf("Size\tMemory\n");
    compareMemory(512, out);
    compareMemory(1024, out);
    compareMemory(4096, out);

    printf("\nBamboo Insert/Remove\n");
    compareTimeBamboo(512, out);
    compareTimeBamboo(1024, out);
    compareTimeBamboo(4096, out);
}
