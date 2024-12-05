#include "../inc/PrimeNumber.h"

bool isPrime(int value)
{
    for (int i = 2; i * i <= value; ++i)
        if (value % i == 0)
            return false;
    return true;
}

int getNextPrime(int value)
{
    while (!isPrime(++value))
        ;
    return value;
}
