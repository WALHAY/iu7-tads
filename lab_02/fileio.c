#include "fileio.h"

FILE *open_file(char *name, char *mode, int *rc)
{
    FILE *file = fopen(name, mode);
    if (file == NULL)
        *rc = IO_ERR;
    return file;
}

void close_file(FILE *file)
{
    if (file)
        fclose(file);
}
