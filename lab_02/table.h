#pragma once

#include "books.h"
#include <stdlib.h>
#include <string.h>

typedef struct
{
    size_t size;
    size_t *keySet;
    Book *entrySet;
} Table;

bool compare_publishers(Book *first, Book *second);

void swap_keys(size_t *first, size_t *second);

void sort_table(Table *table);

void add_entry(Table *table, Book *entry);

void remove_entry(Table *table, size_t index);

void print_table_by_keys(Table *table);

void print_table_by_data(Table *table);
