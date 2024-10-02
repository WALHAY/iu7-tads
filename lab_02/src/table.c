#include "../inc/table.h"

int get_entries_count_in_file(FILE *file, size_t entry_size, size_t *count)
{
    if (!file || !count)
        return NULLPTR_ERROR;

    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    if (size % entry_size != 0)
        return WRONG_FILE_FMT_ERROR;

    *count = size / entry_size;
    return SUCCESS;
}

bool compare_keys(Key *first, Key *second)
{
    if (!first || !second)
        return 0;

    return strcmp(first->authorSurname, second->authorSurname) > 0;
}

bool compare_entries(Book *first, Book *second)
{
    if (!first || !second)
        return 0;

    return strcmp(first->authorSurname, second->authorSurname) > 0;
}

void swap_keys(Key *first, Key *second)
{
    if (!first || !second)
        return;

    Key temp = *first;
    *first = *second;
    *second = temp;
}

void swap_entries(Book *first, Book *second)
{
    if (!first || !second)
        return;

    Book temp = *first;
    *first = *second;
    *second = temp;
}

void bsort_table_by_keys(Table *table)
{
    if (!table)
        return;

    if (table->size <= 1)
        return;

    for (size_t i = 0; i < table->size - 1; ++i)
        for (size_t j = 0; j < table->size - i - 1; ++j)
            if (compare_keys(table->keySet + j, table->keySet + j + 1))
                swap_keys(table->keySet + j, table->keySet + j + 1);
}

void bsort_table_by_entries(Table *table)
{
    if (!table)
        return;

    if (table->size <= 1)
        return;

    for (size_t i = 0; i < table->size - 1; ++i)
        for (size_t j = 0; j < table->size - i - 1; ++j)
            if (compare_entries(table->entrySet + j, table->entrySet + j + 1))
                swap_entries(table->entrySet + j, table->entrySet + j + 1);
}

static int qcompare_keys(const void *first, const void *second)
{
    return compare_keys((Key *)first, (Key *)second);
}

static int qcompare_entries(const void *first, const void *second)
{
    return compare_entries((Book *)first, (Book *)second);
}

void qsort_table_by_keys(Table *table)
{
    if (!table)
        return;

    qsort(table->keySet, table->size, sizeof(Key), qcompare_keys);
}

void qsort_table_by_entries(Table *table)
{
    if (!table)
        return;

    qsort(table->entrySet, table->size, sizeof(Book), qcompare_entries);
}

int generate_key_array(Table *table)
{
    if (!table)
        return NULLPTR_ERROR;

    if (!table->size)
        return EMPTY_TABLE;

    for (size_t i = 0; i < table->size; ++i)
    {
        strcpy(table->keySet[i].authorSurname, table->entrySet[i].authorSurname);
        table->keySet[i].index = i;
    }
    return SUCCESS;
}

int add_entry(Table *table, Book *entry)
{
    if (!table || !entry)
        return NULLPTR_ERROR;

    if (table->size >= MAX_ENTRIES)
        return ADD_OVERFLOW;

    size_t index = table->size;
    table->entrySet[index] = *entry;
    strcpy(table->keySet[index].authorSurname, entry->authorSurname);
    table->keySet[index].index = index;
    table->size++;
    return SUCCESS;
}

int remove_first_by_title(Table *table, char *title)
{
    if (!table || !title)
        return NULLPTR_ERROR;

    bool found = false;
    size_t found_index = 0;
    for (size_t i = 0; i < table->size; ++i)
    {
        if (!strcmp(title, table->entrySet[i].bookTitle))
        {
            found = true;
            found_index = i;
            break;
        }
    }

    if (!found)
        return NOT_FOUND;

    table->size--;
    for (size_t i = found_index; i < table->size; ++i)
        table->entrySet[i] = table->entrySet[i + 1];

    return SUCCESS;
}

int find_all_novels_by_author(Table *table, char *author)
{
    if (!table)
        return NULLPTR_ERROR;

    if (!table->size)
        return EMPTY_TABLE;

    bool found = false;
    for (size_t i = 0; i < table->size; ++i)
    {
        Book *book = table->entrySet + i;
        if (!strcmp(author, book->authorSurname))
        {
            if (book->genre == FICTION && book->data.fiction.type == NOVEL)
            {
                printf("\nEntry #%zu\n", i + 1);
                print_book(table->entrySet + i);
                found = true;
            }
        }
    }

    return found ? SUCCESS : NOT_FOUND;
}

int print_key_array(Table *table)
{
    if (!table)
        return NULLPTR_ERROR;

    if (!table->size)
        return EMPTY_TABLE;

    printf("\nKey\tIndex\n");

    for (size_t i = 0; i < table->size; ++i)
        printf("%s\t%zu\n", table->keySet[i].authorSurname, table->keySet[i].index);
    return SUCCESS;
}

int print_table_by_keys(Table *table)
{
    if (!table)
        return NULLPTR_ERROR;

    if (!table->size)
        return EMPTY_TABLE;

    for (size_t i = 0; i < table->size; ++i)
    {
        printf("\nEntry #%zu\n", i + 1);
        print_book(table->entrySet + table->keySet[i].index);
    }
    return SUCCESS;
}

int print_table_by_entries(Table *table)
{
    if (!table)
        return NULLPTR_ERROR;

    if (!table->size)
        return EMPTY_TABLE;

    for (size_t i = 0; i < table->size; ++i)
    {
        printf("\nEntry #%zu\n", i + 1);
        print_book(table->entrySet + i);
    }
    return SUCCESS;
}

int import_table_from_file(Table *table, FILE *file)
{
    if (!table || !file)
        return NULLPTR_ERROR;

    size_t count = 0;
    if (get_entries_count_in_file(file, sizeof(Book), &count))
        return WRONG_FILE_FMT_ERROR;

    if (fread(table->entrySet, sizeof(Book), count, file) != count)
        return READ_ERROR;
    table->size = count;
    return generate_key_array(table);
}

int export_table_to_file(Table *table, FILE *file)
{
    if (!table || !file)
        return NULLPTR_ERROR;

    fwrite(table->entrySet, sizeof(Book), table->size, file);
    return SUCCESS;
}
