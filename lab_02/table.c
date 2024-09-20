#include "table.h"

bool compare_publishers(Book *first, Book *second)
{
    return strcmp(first->bookTitle, second->bookTitle) > 0;
}

void swap_keys(size_t *first, size_t *second)
{
    size_t temp = *first;
    *first = *second;
    *second = temp;
}

void sort_table(Table *table)
{
    for (size_t i = 0; i < table->size; ++i)
        for (size_t j = i; j < table->size; ++j)
            if (compare_publishers(table->entrySet + table->keySet[i], table->entrySet + table->keySet[j]))
                swap_keys(table->keySet + i, table->keySet + j);
}

void add_entry(Table *table, Book *entry);

void remove_entry(Table *table, size_t index);

void print_table_by_keys(Table *table);

void print_table_by_data(Table *table);
