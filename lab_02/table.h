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

void remove_entry_by_key(Table *table, char *field);

void print_by_author(Table *table, char *author);

void print_table_by_keys(Table *table);

void print_table_by_entries(Table *table);

size_t import_table_from_file(FILE *file, Table *table);

size_t export_table_to_file(FILE *file, Table *table);
