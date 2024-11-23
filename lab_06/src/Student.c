#include "../inc/Student.h"

int surnameComparator(const StudentData *first, const StudentData *second)
{
    return strcmp(first->name, second->name);
}

int scoreComparator(const StudentData *first, const StudentData *second)
{
    double firstd = first->score;
    double secondd = second->score;

    return firstd > secondd ? 1 : -(firstd < secondd);
}

bool scoreFilter(const StudentData *first)
{
    return first->score > 2;
}

StudentData *createData(char *name, float score, int *rc)
{
    StudentData *data = malloc(sizeof(StudentData));
    if (data)
    {
        data->name = strdup(name);
        data->score = score;
    }
    else
        *rc = ALLOC_ERROR;
    return data;
}

void printStudent(StudentData *data)
{
    if (!data)
        return;

    printf("%s: %.2f\n", data->name, data->score);
}

void freeData(StudentData *data)
{
    if (data)
    {
        free(data->name);
        free(data);
    }
}
