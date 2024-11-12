#include "../inc/Student.h"

StudentData *createData(const char *name, float score, int *rc)
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

void freeData(StudentData *data);
