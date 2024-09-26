#include "tui.h"

static int safe_int_input(int *value)
{
    char temp[20];
    fgets(temp, 20, stdin);
    char *end = NULL;
    long val = strtol(temp, &end, 10);
    if (errno == ERANGE)
        return NAN_ERROR;
    *value = val;
    return SUCCESS;
}

void print_rules(void)
{
    printf("Программа для взаимодействия с таблицей книг\n"
           "Возможности программы: удаление/добавление записей в таблицу\n"
           "Сортировка по ключам/записям, поиск книг по автору\n\n");
}

int execute_operation(Table *table)
{
    char *options[] = {"Sort using keys", "Sort using entries", "Add book",    "Remove book", "Find by key",
                       "Print keys",      "Print entries",      "Import data", "Export data", "Quit"};
    switch (input_enum(10, options))
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

        return add_entry(table, &book);
    }
    case REMOVE_ENTRY:
    {
        char title[MAX_TITLE_LEN];
        validate_input(title, "title to remove", MAX_TITLE_LEN);
        return remove_entry_by_key(table, title);
    }
    case FIND_BY_KEY:
    {
        char title[MAX_TITLE_LEN];
        validate_input(title, "author to find", MAX_TITLE_LEN);
        return print_by_author(table, title);
    }
    case PRINT_ENTRIES:
        return print_table_by_entries(table);
    case PRINT_KEYS:
        return print_table_by_keys(table);
    case IMPORT_TABLE:
    {
        char filename[MAX_FILENAME_LEN + 1];

        int rc = SUCCESS;
        FILE *file = NULL;
        validate_input(filename, "file to import", MAX_FILENAME_LEN);
        file = open_file(filename, "rb", &rc);
        if(file == NULL || rc)
            return rc;

        printf("%s\n", get_error_message(rc));
        rc = import_table_from_file(table, file);
        close_file(file);
        return rc;
    }
case EXPORT_TABLE:
{
    char filename[MAX_FILENAME_LEN + 1];

    int rc = SUCCESS;
    FILE *file = NULL;
    while (true)
    {
        validate_input(filename, "file to export", MAX_FILENAME_LEN);
        file = open_file(filename, "wb", &rc);
        if (file != NULL && !rc)
            break;
        printf("%s\n", get_error_message(rc));
    }
    rc = export_table_to_file(table, file);
    close_file(file);
    return rc;
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

size_t input_enum(size_t max_options, char **options)
{
    printf("\nPossible variants:\n");
    for (size_t i = 0; i < max_options; ++i)
        printf("\t%zu. %s\n", i, options[i]);

    size_t option = 0;
    printf("Option: ");
    while (safe_int_input((int *)&option) || option >= max_options)
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

char *get_error_message(int error)
{
    switch (error)
    {
    case SUCCESS:
        return "Warning: Everything is fine! IDK?";
    case NULLPTR_ERROR:
        return "Error: Null pointer passed to function!";
    case OPEN_FILE_ERROR:
        return "Error: Failed to open file!";
    case WRONG_FILE_FMT_ERROR:
        return "Error: Wrong file or corrupted file!";
    case READ_ERROR:
        return "Error: Failed to read data from file!";
    case ADD_OVERFLOW:
        return "Error: Failed to add entry to table because of max size of table!";
    case NAN_ERROR:
        return "Error: Failed to input number!(Possibly wrong symbols were used)";
    case NOT_FOUND:
        return "Error: Entry wasn't found";
    case EMPTY_TABLE:
        return "Error: Table is empty!";
    }
    return "Error: Error message not specified!";
}
