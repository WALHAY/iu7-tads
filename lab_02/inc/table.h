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
    Key keySet[MAX_ENTRIES];
    Book entrySet[MAX_ENTRIES];
} Table;

bool compare_keys(Key *first, Key *second);

bool compare_entries(Book *first, Book *second);

void swap_keys(Key *first, Key *second);

void swap_entries(Book *first, Book *second);

void bsort_table_by_keys(Table *table);

void bsort_table_by_entries(Table *table);

void qsort_table_by_keys(Table *table);

void qsort_table_by_entries(Table *table);

void generate_key_array(Table *table);

int add_entry(Table *table, Book *entry);

int remove_entry_by_key(Table *table, char *title);

int print_by_author(Table *table, char *author);

int print_key_array(Table *table);

int print_table_by_keys(Table *table);

int print_table_by_entries(Table *table);

int import_table_from_file(Table *table, FILE *file);

int export_table_to_file(Table *table, FILE *file);
