#include "../inc/Student.h"

StudentData *createData(char *name, float score, int *rc)
{
    StudentData *data = malloc(sizeof(StudentData));
    if (data)
    {
        data->name = name;
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

    printf("%s: %f\n", data->name, data->score);
}

void freeData(StudentData *data)
{
    if (data)
    {
        free(data->name);
        free(data);
    }
}
