#include "table.h"
#include "tui.h"

int main(void)
{
    print_rules();
    Table table = {.size = 0, .max_size = MAX_ENTRIES};

    int rc = SUCCESS;

    while (!rc)
        rc = execute_operation(&table);

    return SUCCESS;
}
