#include "tui.h"

void print_rules(void)
{
    printf("Программа для взаимодействия с таблицей книг\n"
           "Возможности программы: удаление/добавление записей в таблицу\n"
           "Сортировка по ключам/записям, поиск книг по автору\n\n");
}

int execute_operation(Table *table)
{
    char *options[] = {"Sort using keys", "Sort using entries", "Add book",    "Find by key", "Print keys",
                       "Print entries",   "Import data",        "Export data", "Quit"};
    switch (input_enum(9, options))
    {
    case SORT_ENTRIES:
        sort_table_by_entries(table);
        printf("Table sorted using entries!\n");
        break;
    case SORT_KEYS:
        sort_table_by_keys(table);
        printf("Table sorted using keys!\n");
        break;
    case ADD_ENTRY:
    {
        Book book;
        input_book(&book);

        add_entry(table, &book);
        break;
    }
    case FIND_BY_KEY:
        break;
    case PRINT_ENTRIES:
        print_table_by_entries(table);
        break;
    case PRINT_KEYS:
        print_table_by_keys(table);
        break;
    case IMPORT_TABLE:
    {
        char filename[MAX_FILENAME_LEN + 1];

        int local_rc = SUCCESS;
        FILE *file = NULL;
        while (true)
        {
            validate_input(filename, "filename to import data", MAX_FILENAME_LEN);
            file = open_file(filename, "rb", &local_rc);
            if (file != NULL && !local_rc)
                break;
            printf("Error: Failed to read file\n");
        }
        printf("Start reading %s\n", filename);
        import_table_from_file(table, file);
        close_file(file);
        break;
    }
    case EXPORT_TABLE:
    {
        char filename[MAX_FILENAME_LEN + 1];

        int local_rc = SUCCESS;
        FILE *file = NULL;
        while (true)
        {
            validate_input(filename, "filename to export data", MAX_FILENAME_LEN);
            file = open_file(filename, "wb", &local_rc);
            if (file != NULL && !local_rc)
                break;
            printf("Error: Wrong Filename\n");
        }
        printf("Start writing %s\n", filename);
        export_table_to_file(table, file);
        close_file(file);
        break;
    }
    case QUIT:
        printf("Exiting process...\n");
        exit(SUCCESS);
    }

    return SUCCESS;
}

void validate_input(char *field, char *title, size_t max_size)
{
    char temp[max_size + 1];
    while (true)
    {
        printf("Enter %s: ", title);
        fgets(temp, max_size + 1, stdin);
        temp[strcspn(temp, "\n")] = '\0';
        size_t len = strlen(temp);
        if (len == 0)
        {
            printf("Error: Empty string!\n");
            continue;
        }

        if (len > max_size)
        {
            printf("Error: String overflow!\n");
            continue;
        }
        break;
    }
    strcpy(field, temp);
}

static int safe_int_input(int *value)
{
    char temp[20];
    scanf("%19s", temp);
    char *end = NULL;
    long val = strtol(temp, &end, 10);
    if (errno == ERANGE)
        return NAN_ERROR;
    *value = val;
    return SUCCESS;
}

size_t input_enum(size_t max_options, char **options)
{
    printf("Possible variants:\n");
    for (size_t i = 0; i < max_options; ++i)
        printf("\t%zu. %s\n", i, options[i]);

    size_t option = 0;
    printf("Option: ");
    while (safe_int_input((int*)&option) || option >= max_options)
        printf("Error: Wrong option!\nEnter option again: ");
    return option;
}

size_t input_value(char *title, bool min_limit, bool max_limit, int min_value, int max_value)
{
    int value = 0;
    printf("Enter %s: ", title);
    while (safe_int_input(&value) || (max_limit && value > max_value) || (min_limit && value < min_value))
        printf("Error: Wrong value!\nEnter %s again: ", title);
    return value;
}
