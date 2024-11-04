#include "../inc/QueueLogic.h"
#include <time.h>

int main(void)
{
    srand(time(NULL));
    TimeSpecification timings = {1, 5, 0, 3, 0, 4, 0, 1};
    taskArray(1000, &timings);
    return 0;
}
