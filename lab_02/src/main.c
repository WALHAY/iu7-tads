#include "../inc/entry_generator.h"
#include "../inc/table.h"
#include "../inc/tui.h"

int main(int argc, char **argv)
{
    Table table = {.size = 0};
    if (argc == 3)
    {
        generate_entries(&table, atoi(argv[2]));
        printf("Entries generated!\n");
    }

    print_rules();
    print_limitations();

    int rc = SUCCESS;

    while (true)
        if ((rc = execute_operation(&table)))
            printf("%s\n", get_error_message(rc));

    return SUCCESS;
}
