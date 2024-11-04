#include "../inc/Defines.h"
#include "../inc/LinkedQueue.h"
#include "../inc/QueueLogic.h"
#include <time.h>

int main(void)
{
    srand(time(NULL));
    TimeSpecification timings = {1, 5, 0, 3, 0, 4, 0, 1};
    task(1000, &timings);
    return 0;
}
