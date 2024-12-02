#include "../inc/TextUserInterface.h"

int main(void)
{
    while (true)
    {
        int rc = executeOperation();
        if (rc)
            printf("%s\n", getErrorMessage(rc));
    }
    return 0;
}
