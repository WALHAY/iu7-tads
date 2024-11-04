#include "../inc/QueueLogic.h"
#include "../inc/ArrayQueue.h"
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int rc = SUCCESS;
    TimeSpecification timings = {1, 5, 0, 3, 0, 4, 0, 1};
    task(1000, &timings);
    return 0;
}
