#include "table.h"
#include "tui.h"

int main(void)
{
    Table table = {.size = 0, .max_size = 40};

    while (true)
    {
        execute_operation(&table);
    }

    return SUCCESS;
}
