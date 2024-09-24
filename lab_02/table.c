#include "table.h"

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

void add_entry(Table *table, Book *entry)
{
    if (table->size >= table->max_size)
        return;

    table->entrySet[table->size] = *entry;
    table->keySet[table->size] = (Key){entry->authorSurname, table->size++};
}

void remove_entry_by_key(Table *table, char *field)
{
    for (size_t i = 0; i < table->size; ++i)
    {
        if (!strcmp(field, table->keySet[i].authorSurname))
        {
        }
    }
}

static void print_column(size_t length, char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    size_t diff = length - strlen(text);

    printf("|");
    size_t i = 0;
    for (; i <= diff / 2; ++i)
        printf(" ");
    printf(format, ap);
    for (; i <= diff; ++i)
        printf(" ");
    va_end(ap);
}

// author - title - publisher - pages - type -
void print_table_entry(Book *entry)
{
    print_column(entry->authorSurname, MAX_SURNAME_LEN + 2);
    print_column(entry->bookTitle, MAX_TITLE_LEN + 2);
    print_column(entry->publisher, MAX_PUBLISHER_LEN + 2);
    print_column(itoa(entry->pageCount), 10);
}

void print_table_by_keys(Table *table);

void print_table_by_entries(Table *table);
