#include "tui.h"

void print_rules(void)
{
    printf("Программа для взаимодействия с таблицей книг\n"
           "Возможности программы: удаление/добавление записей в таблицу\n"
           "Сортировка по ключам/записям, поиск книг по автору\n\n");
}

void execute_operation(Table *table)
{
    char *options[] = {"Sort using keys", "Sort using entries", "Find by key", "Print keys", "Print entries"};
    size_t opcode = 0;
    input_enum(&opcode, 5, options);
    switch (opcode)
    {
    case SORT_KEYS:
        sort_table_by_keys(table);
        break;
    case SORT_ENTRIES:
        sort_table_by_entries(table);
        break;
    case FIND_BY_KEY:
        break;
    case PRINT_KEYS:
        print_table_by_keys(table);
        break;
    case PRINT_ENTRIES:
        print_table_by_entries(table);
        break;
    case IMPORT_TABLE:
        import_table_from_file(table);
        break;
    }
}

int validate_input(char *field, char *title, size_t max_size)
{
    char temp[max_size + 1];
    do
    {
        printf("Enter %s: ", title);
        fgets(temp, max_size, stdin);
    } while (strlen(temp) >= max_size);
    char *newline = strchr(temp, '\n');
    if (newline)
        *newline = '\0';
    strcpy(field, temp);
    return SUCCESS;
}

int input_enum(size_t *option, size_t max_options, char **options)
{
    printf("\nPossible variants:\n");
    for (size_t i = 0; i < max_options; ++i)
        printf("\t%zu. %s\n", i, options[i]);

    printf("Option: ");
    while (!scanf("%zu", option) || *option >= max_options)
        printf("\nWrong option! Enter option again: ");
    return SUCCESS;
}

int input_value(size_t *value, char *title, bool has_range, size_t max_value)
{
    printf("Enter %s: ", title);
    while (!scanf("%zu", value) || (has_range && *value > max_value))
        printf("Enter %s again: ", title);
    return SUCCESS;
}
