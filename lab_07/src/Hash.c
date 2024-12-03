#include "../inc/Hash.h"

hash_t getStringHash(const char *string)
{
    hash_t hash = 0;
    size_t index = 0;
    hash_t ppow = 1;
    while (string[index] != '\0')
    {
        hash += string[index++] * ppow;
        ppow *= 31;
    }
    return hash;
}
