#include "../inc/tui.h"

static void print_char_i_times(char c, size_t i)
{
    for (size_t j = 0; j < i; ++j)
        printf("%c", c);
}

void print_splitter(void)
{
    printf("+");
    print_char_i_times('-', MAX_OUT_SURNAME_LEN + 2);
    printf("+");
    print_char_i_times('-', MAX_OUT_TITLE_LEN + 2);
    printf("+");
    print_char_i_times('-', MAX_OUT_PUBLISHER_LEN + 2);
    printf("+");
    print_char_i_times('-', MAX_OUT_PAGES_WIDTH + 2);
    printf("+");
    // technical literature part
    print_char_i_times('-', MAX_OUT_INDUSTRY_LEN + 2);
    printf("+");
    print_char_i_times('-', MAX_OUT_DOMESTIC_WIDTH + 2);
    printf("+");
    print_char_i_times('-', MAX_OUT_YEAR_WIDTH + 2);
    printf("+");
    // fiction literature part
    print_char_i_times('-', MAX_OUT_TYPE_WIDTH + 2);
    printf("+");
    // children literature part
    print_char_i_times('-', MAX_OUT_AGE_WIDTH + 2);
    printf("+\n");
}

static void print_column(char *text, size_t length)
{
    int diff = length - strlen(text) + 2;
    int half_diff = diff / 2;
    int add = diff - half_diff;
    printf("|");
    for (int i = 0; i < half_diff; ++i)
        printf(" ");
    printf("%s", text);
    for (int i = 0; i < add; ++i)
        printf(" ");
}

void print_table_header(void)
{
    print_splitter();
    print_column("Author", MAX_OUT_SURNAME_LEN);
    print_column("Title", MAX_OUT_TITLE_LEN);
    print_column("Publisher", MAX_OUT_PUBLISHER_LEN);
    print_column("Pages", MAX_OUT_PAGES_WIDTH);
    // technical literature part
    print_column("Industry", MAX_OUT_INDUSTRY_LEN);
    print_column("Country", MAX_OUT_DOMESTIC_WIDTH);
    print_column("Year", MAX_OUT_YEAR_WIDTH);
    // fiction literature part
    print_column("Type", MAX_OUT_TYPE_WIDTH);
    // children literature part
    print_column("Min age", MAX_OUT_AGE_WIDTH);
    printf("|\n");
    print_splitter();
}
// author - title - publisher - pages - type
void print_table_entry(Book *entry)
{
    print_column(entry->authorSurname, MAX_OUT_SURNAME_LEN);
    print_column(entry->bookTitle, MAX_OUT_TITLE_LEN);
    print_column(entry->publisher, MAX_OUT_PUBLISHER_LEN);
    char pages[MAX_OUT_PAGES_WIDTH + 1];
    sprintf(pages, "%zu", entry->pageCount);
    print_column(pages, MAX_OUT_PAGES_WIDTH);
    // technical literature part
    bool technical = entry->genre == TECHNICAL;
    print_column(technical ? entry->data.technical.industry : "-", MAX_OUT_INDUSTRY_LEN);
    print_column(technical ? (entry->data.technical.domestic ? "Domestic" : "Non Domestic") : "-",
                 MAX_OUT_DOMESTIC_WIDTH);
    char year[MAX_OUT_YEAR_WIDTH + 1];
    sprintf(year, (technical ? "%zu" : "-"), entry->data.technical.publishYear);
    print_column(year, MAX_OUT_YEAR_WIDTH);
    // fiction literature part
    bool print_type = entry->genre == FICTION || entry->genre == CHILDREN;
    print_column(print_type ? get_fiction_book_type(&entry->data.fiction) : "-", MAX_OUT_TYPE_WIDTH);
    // children literature part
    bool children = entry->genre == CHILDREN;
    char minimalAge[MAX_OUT_AGE_WIDTH + 1];
    sprintf(minimalAge, (children ? "%zu" : "-"), entry->data.children.minimalAge);
    print_column(minimalAge, MAX_OUT_AGE_WIDTH);
    printf("|\n");
}

static int safe_int_input(int *value)
{
    char temp[20];
    fgets(temp, 20, stdin);
    char *end = NULL;
    errno = 0;
    long val = strtol(temp, &end, 10);
    if (errno == ERANGE || errno == EINVAL)
        return NAN_ERROR;
    *value = val;
    return SUCCESS;
}

void print_rules(void)
{
    printf("Program to interact with tables of book structures\n"
           "Abilities: add/remove book, sort in different algorithms\n"
           "Find by author, Time and memory comparison\n"
           "Import/export data tables to files\n\n");
}

void print_limitations(void)
{
    printf("Limitations:\n\n"
           " - Max surname is %d symbols!\n"
           " - Max book title is %d symbols!\n"
           " - Max publisher name is %d sybols!\n"
           " - Max industry name is %d symbols!\n"
           " - Max filename is %d symbols!\n\n",
           MAX_SURNAME_LEN, MAX_TITLE_LEN, MAX_PUBLISHER_LEN, MAX_INDUSTRY_LEN, MAX_FILENAME_LEN);
}

int execute_operation(Table *table)
{
    char *options[] = {"Add book",
                       "Remove book by title",
                       "Find novels by author",
                       "Print key array",
                       "Print table using keys",
                       "Print table using entries",
                       "Entries Bubble Sort",
                       "Keys Bubble Sort",
                       "Entries QSort",
                       "Keys QSort",
                       "Import data",
                       "Export data",
                       "Collect efficiency",
                       "Quit"};
    size_t opt = input_enum(14, options);
    printf("Processing: %s\n", *(options + opt));
    switch (opt)
    {
    case ADD_ENTRY:
    {
        Book book;
        input_book(&book);

        return add_entry(table, &book);
    }
    case REMOVE_ENTRY:
    {
        char title[MAX_TITLE_LEN];
        input_string(title, "title to remove", MAX_TITLE_LEN);
        return remove_first_by_title(table, title);
    }
    case FIND_BY_KEY:
    {
        char title[MAX_TITLE_LEN];
        input_string(title, "author to find novels", MAX_TITLE_LEN);
        return find_all_novels_by_author(table, title);
    }
    case PRINT_KEY_ARRAY:
        return print_key_array(table);
    case PRINT_KEYS:
        return print_table_by_keys(table);
    case PRINT_ENTRIES:
        return print_table_by_entries(table);
    case BSORT_ENTRIES:
        bsort_table_by_entries(table);
        generate_key_array(table);
        break;
    case BSORT_KEYS:
        bsort_table_by_keys(table);
        break;
    case QSORT_ENTRIES:
        qsort_table_by_entries(table);
        generate_key_array(table);
        break;
    case QSORT_KEYS:
        qsort_table_by_keys(table);
        break;
    case IMPORT_TABLE:
    {
        char filename[MAX_FILENAME_LEN + 1];

        int rc = SUCCESS;
        FILE *file = NULL;
        input_string(filename, "file to import", MAX_FILENAME_LEN);
        rc = validate_filename(filename);

        if (!rc)
            file = open_file(filename, "rb", &rc);

        if (rc)
            return rc;

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
            input_string(filename, "file to export", MAX_FILENAME_LEN);
            rc = validate_filename(filename);
            if (!rc)
                file = open_file(filename, "wb", &rc);

            if (file != NULL && !rc)
                break;

            printf("%s\n", get_error_message(rc));
        }
        rc = export_table_to_file(table, file);
        close_file(file);
        return rc;
    }
    case EFFICIENCY:
        get_program_efficiency();
        break;
    case QUIT:
        printf("Exiting process...\n");
        exit(SUCCESS);
    }

    return SUCCESS;
}

void input_string(char *field, char *title, size_t max_size)
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
        return "Error: Book not found!";
    case EMPTY_TABLE:
        return "Error: Table is empty!";
    case WRONG_FILENAME_ERROR:
        return "Error: Wrong filename format!";
    }
    return "Error: Error message not specified!";
}

int validate_filename(char *filename)
{
    if (!filename)
        return NULLPTR_ERROR;

    char *dot = strchr(filename, '.');
    if (!dot || dot - filename <= 0)
        return WRONG_FILENAME_ERROR;

    if (strcmp(dot + 1, "tbl"))
        return WRONG_FILENAME_ERROR;

    return SUCCESS;
}
