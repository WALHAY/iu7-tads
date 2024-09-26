#include "table.h"
#include "tui.h"

int main(void)
{
    print_rules();
    Table table = {.size = 0, .max_size = MAX_ENTRIES};

    int rc = SUCCESS;

    while (true)
    {
        rc = execute_operation(&table);
        if(rc)
            printf("%s\n", get_error_message(rc));
    }

    return SUCCESS;
}
