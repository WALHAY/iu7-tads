#include "../inc/table.h"
#include "../inc/tui.h"

int main(void)
{
    print_rules();
    Table table = {.size = 0, .max_size = MAX_ENTRIES};

    int rc = SUCCESS;

    while (true)
        if ((rc = execute_operation(&table)))
            printf("%s\n", get_error_message(rc));

    return SUCCESS;
}
