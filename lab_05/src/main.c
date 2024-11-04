#include "../inc/TextUserInterface.h"
#include <time.h>

int main(void)
{
    srand(time(NULL));
    while (true)
    {
        int rc = executeOperation();
        if (rc)
            printf("%s\n", getErrorMessage(rc));
    }
    return 0;
}
