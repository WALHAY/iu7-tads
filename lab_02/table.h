#pragma once

#include "books.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *authorSurname;
    size_t index;
} Key;

typedef struct
{
    size_t size;
    size_t max_size;
    Key *keySet;
    Book *entrySet;
} Table;

bool compare_keys(Key *first, Key *second);

bool compare_entries(Book *first, Book *second);

void swap_keys(Key *first, Key *second);

void swap_entries(Book *first, Book *second);

void sort_table_by_keys(Table *table);

void sort_table_by_entries(Table *table);

void generate_key_array(Table *table);

void add_entry(Table *table, Book *entry);

void remove_entry(Table *table, size_t index);

void print_table_entry(Book *entry);

void print_table_by_keys(Table *table);

void print_table_by_entries(Table *table);
