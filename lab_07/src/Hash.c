#include "../inc/Hash.h"

hash_t xorshift(hash_t n, int i)
{
    return n ^ (n >> i);
}

hash_t getIntHash(int x)
{
    hash_t p = 0x5555555555555555ULL;   // pattern of alternating 0 and 1
    hash_t c = 17316035218449499591ULL; // random uneven integer constant;
    return c * xorshift(p * xorshift(x, 32), 32);
}
