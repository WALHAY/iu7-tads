#include "../inc/Comparison.h"

#define TRIES 1

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
            head = treeInsert(head, arr[j], surnameComparator, &rc);
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

    insert /= TRIES;
    remove /= TRIES;
    fprintf(out, "%zu\t%zu\t%zu\n", elements, insert, remove);
}

static void restructureArray(StudentData **newArr, StudentData **arr, size_t l, size_t r, size_t *lastIndex)
{
    if (l - r <= 1 || r - l <= 1)
        return;
    size_t middle = (r + l) / 2;
    newArr[*lastIndex] = arr[middle];
    *lastIndex += 1;
    restructureArray(newArr, arr, l, middle, lastIndex);
    restructureArray(newArr, arr, middle, r, lastIndex);
}

static void compareTimePerfect(size_t elements, FILE *out)
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
        StudentData *newArr[elements];
        size_t lastIndex = 0;
        restructureArray(newArr, arr, 0, elements, &lastIndex);

        size_t l_insert = 0;
        for (size_t j = 0; j < elements - 1; ++j)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            head = treeInsert(head, newArr[j], surnameComparator, &rc);
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
    compareMemory(500, out);
    compareMemory(1000, out);
    compareMemory(5000, out);

    printf("\nBamboo Insert/Remove\n");
    compareTimeBamboo(500, out);
    compareTimeBamboo(1000, out);
    compareTimeBamboo(5000, out);

    printf("\nPerfect Insert/Remove\n");
    compareTimePerfect(500, out);
    compareTimePerfect(1000, out);
    compareTimePerfect(5000, out);
}
