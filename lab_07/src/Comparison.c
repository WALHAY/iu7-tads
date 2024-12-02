#include "../inc/Comparison.h"

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

void compareTaDS(FILE *out)
{
    printf("Size\tMemory\tInsert\tFind\tComparisons\n");
}
