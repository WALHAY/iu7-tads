#include "table.h"

static size_t get_entries_count_in_file(FILE *file, size_t entry_size, int *rc)
{
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    if(size % entry_size != 0)
        *rc = WRONG_FILE;
    return size / entry_size;
}

static void print_char_i_times(char c, size_t i)
{
    for (size_t j = 0; j < i; ++j)
        printf("%c", c);
}

static void print_splitter(void)
{
    printf("+");
    print_char_i_times('-', MAX_SURNAME_LEN + 2);
    printf("+");
    print_char_i_times('-', MAX_TITLE_LEN + 2);
    printf("+");
    print_char_i_times('-', MAX_PUBLISHER_LEN + 2);
    printf("+");
    print_char_i_times('-', MAX_PAGES_WIDTH + 2);
    printf("+");
    // technical literature part
    print_char_i_times('-', MAX_INDUSTRY_LEN + 2);
    printf("+");
    print_char_i_times('-', MAX_DOMESTIC_WIDTH + 2);
    printf("+");
    print_char_i_times('-', MAX_YEAR_WIDTH + 2);
    printf("+");
    // fiction literature part
    print_char_i_times('-', MAX_TYPE_WIDTH + 2);
    printf("+");
    // children literature part
    print_char_i_times('-', MAX_AGE_WIDTH + 2);
    printf("+\n");
}

static void print_column(char *text, size_t length)
{
    size_t diff = length - strlen(text) + 2;
    size_t half_diff = diff / 2;
    size_t add = diff - half_diff;

    printf("|");
    for (size_t i = 0; i < half_diff; ++i)
        printf(" ");
    printf("%s", text);
    for (size_t i = 0; i < add; ++i)
        printf(" ");
}

static void print_table_header(void)
{
    print_splitter();
    print_column("Author", MAX_SURNAME_LEN);
    print_column("Title", MAX_TITLE_LEN);
    print_column("Publisher", MAX_PUBLISHER_LEN);
    print_column("Pages", MAX_PAGES_WIDTH);
    // technical literature part
    print_column("Industry", MAX_INDUSTRY_LEN);
    print_column("Country", MAX_DOMESTIC_WIDTH);
    print_column("Year", MAX_YEAR_WIDTH);
    // fiction literature part
    print_column("Type", MAX_TYPE_WIDTH);
    // children literature part
    print_column("Min age", MAX_AGE_WIDTH);
    printf("|\n");
    print_splitter();
}

// author - title - publisher - pages - type -
static void print_table_entry(Book *entry)
{
    print_column(entry->authorSurname, MAX_SURNAME_LEN);
    print_column(entry->bookTitle, MAX_TITLE_LEN);
    print_column(entry->publisher, MAX_PUBLISHER_LEN);
    char pages[MAX_PAGES_WIDTH + 1];
    sprintf(pages, "%zu", entry->pageCount);
    print_column(pages, MAX_PAGES_WIDTH);
    // technical literature part
    bool technical = entry->genre == TECHNICAL;
    print_column(technical ? entry->data.technical.industry : "-", MAX_INDUSTRY_LEN);
    print_column(technical ? (entry->data.technical.domestic ? "Domestic" : "Non Domestic") : "-", MAX_DOMESTIC_WIDTH);
    char year[MAX_YEAR_WIDTH + 1];
    sprintf(year, (technical ? "%zu" : "-"), entry->data.technical.publishYear);
    print_column(year, MAX_YEAR_WIDTH);
    // fiction literature part
    bool print_type = entry->genre == FICTION || entry->genre == CHILDREN;
    print_column(print_type ? get_fiction_book_type(&entry->data.fiction) : "-", MAX_TYPE_WIDTH);
    // children literature part
    bool children = entry->genre == CHILDREN;
    char minimalAge[MAX_AGE_WIDTH + 1];
    sprintf(minimalAge, (children ? "%zu" : "-"), entry->data.children.minimalAge);
    print_column(minimalAge, MAX_AGE_WIDTH);
    printf("|\n");
}

bool compare_keys(Key *first, Key *second)
{
    return strcmp(first->authorSurname, second->authorSurname) > 0;
}

bool compare_entries(Book *first, Book *second)
{
    return strcmp(first->authorSurname, second->authorSurname) > 0;
}

void swap_keys(Key *first, Key *second)
{
    Key temp = *first;
    *first = *second;
    *second = temp;
}

void swap_entries(Book *first, Book *second)
{
    Book temp = *first;
    *first = *second;
    *second = temp;
}

void sort_table_by_keys(Table *table)
{
    for (size_t i = 0; i < table->size; ++i)
        for (size_t j = i; j < table->size; ++j)
            if (compare_keys(table->keySet + i, table->keySet + j))
                swap_keys(table->keySet + i, table->keySet + j);
}

void sort_table_by_entries(Table *table)
{
    for (size_t i = 0; i < table->size; ++i)
        for (size_t j = i; j < table->size; ++j)
            if (compare_entries(table->entrySet + i, table->entrySet + i))
                swap_entries(table->entrySet + i, table->entrySet + j);

    generate_key_array(table);
}

void generate_key_array(Table *table)
{
    for (size_t i = 0; i < table->size; ++i)
        table->keySet[i] = (Key){table->entrySet[i].authorSurname, i};
}

int add_entry(Table *table, Book *entry)
{
    if (table->size >= table->max_size)
        return ADD_OVERFLOW;

    printf("%s", entry->authorSurname);
    table->entrySet[table->size] = *entry;
    table->keySet[table->size] = (Key){entry->authorSurname, table->size++};
    return SUCCESS;
}

void remove_entry_by_key(Table *table, char *field)
{
    for (size_t i = 0; i < table->size; ++i)
        if (!strcmp(field, table->entrySet[i].bookTitle))
            for (size_t j = i; j + 1 < table->size; ++j)
                table->entrySet[j] = table->entrySet[j + 1];
}

void print_by_author(Table *table, char *author)
{
    if (table->size)
    {
        print_table_header();

        for (size_t i = 0; i < table->size; ++i)
            if (!strcmp(author, table->entrySet[i].authorSurname))
                print_table_entry(table->entrySet + i);

        print_splitter();
    }
    else
        printf("Error: Empty table!\n");
}

void print_table_by_keys(Table *table)
{
    if (table->size)
    {
        print_table_header();

        for (size_t i = 0; i < table->size; ++i)
            print_table_entry(table->keySet[i].index + table->entrySet);
        print_splitter();
    }
    else
        printf("Error: Empty table!");
}

void print_table_by_entries(Table *table)
{
    if (table->size)
    {
        print_table_header();

        for (size_t i = 0; i < table->size; ++i)
            print_table_entry(table->entrySet + i);
        print_splitter();
    }
    else
        printf("Error: Empty table!");
}

size_t import_table_from_file(Table *table, FILE *file)
{
    int rc = SUCCESS;
    size_t entries = get_entries_count_in_file(file, sizeof(Book), &rc);
    if (!rc && entries != 0)
    {
        printf("Rc: %d\n", rc);
        fread(table->entrySet, sizeof(Book), entries, file);
        table->size = entries;
        generate_key_array(table);
    }
    return rc;
}

size_t export_table_to_file(Table *table, FILE *file)
{
    fwrite(table->entrySet, sizeof(Book), table->size, file);
    return SUCCESS;
}
