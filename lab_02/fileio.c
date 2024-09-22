#include "fileio.h"

int open_file(const char *filename, const char *mode, FILE **file)
{
    *file = fopen(filename, mode);
    if (!file)
        return IO_ERR;
    return SUCCESS;
}
