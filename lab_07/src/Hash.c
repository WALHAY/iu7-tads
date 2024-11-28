#include "../inc/Hash.h"

hash_t getStringHash(const char *string)
{
    hash_t hash = 0;
    size_t index = 0;
    while (string[index] != '\0')
    {
        hash += string[index] * pow(31, index);
        index++;
    }
    return hash;
}
