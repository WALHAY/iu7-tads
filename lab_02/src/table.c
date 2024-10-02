#include "../inc/table.h"
#include "../inc/tui.h"

static void print_table_splitter(void)
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
    print_char_i_times('-', MAX_OUT_GENRE_LEN + 2);
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

static void print_key_table_splitter(void)
{
    printf("+");
    print_char_i_times('-', MAX_OUT_SURNAME_LEN + 2);
    printf("+");
    print_char_i_times('-', MAX_OUT_INDEX_LEN + 2);
    printf("+\n");
}

static void print_table_header(void)
{
    print_table_splitter();
    print_column("Author", MAX_OUT_SURNAME_LEN);
    print_column("Title", MAX_OUT_TITLE_LEN);
    print_column("Publisher", MAX_OUT_PUBLISHER_LEN);
    print_column("Pages", MAX_OUT_PAGES_WIDTH);
    print_column("Type", MAX_OUT_GENRE_LEN);
    // technical literature part
    print_column("Industry", MAX_OUT_INDUSTRY_LEN);
    print_column("Country", MAX_OUT_DOMESTIC_WIDTH);
    print_column("Year", MAX_OUT_YEAR_WIDTH);
    // fiction literature part
    print_column("Genre", MAX_OUT_TYPE_WIDTH);
    // children literature part
    print_column("Min age", MAX_OUT_AGE_WIDTH);
    printf("|\n");
    print_table_splitter();
}

static void print_key_table_header(void)
{
    print_key_table_splitter();
    print_column("Key", MAX_OUT_SURNAME_LEN);
    print_column("Index", MAX_OUT_INDEX_LEN);
    printf("|\n");
    print_key_table_splitter();
}

// author - title - publisher - pages - type
static void print_table_entry(Book *entry)
{
    print_column(entry->authorSurname, MAX_OUT_SURNAME_LEN);
    print_column(entry->bookTitle, MAX_OUT_TITLE_LEN);
    print_column(entry->publisher, MAX_OUT_PUBLISHER_LEN);
    char pages[MAX_OUT_PAGES_WIDTH + 1];
    sprintf(pages, "%zu", entry->pageCount);
    print_column(pages, MAX_OUT_PAGES_WIDTH);
    print_column(get_book_genre(entry), MAX_OUT_GENRE_LEN);
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

static void print_key_table_entry(Key *entry)
{
    print_column(entry->authorSurname, MAX_OUT_SURNAME_LEN);
    char index[MAX_OUT_INDEX_LEN];
    sprintf(index, "%zu", entry->index);
    print_column(index, MAX_OUT_INDEX_LEN);
    printf("|\n");
}

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

int compare_keys(Key *first, Key *second)
{
    if (!first || !second)
        return 0;

    return strcmp(first->authorSurname, second->authorSurname);
}

int compare_entries(Book *first, Book *second)
{
    if (!first || !second)
        return 0;

    return strcmp(first->authorSurname, second->authorSurname);
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
    if (!table || table->size <= 1)
        return;

    for (size_t i = 0; i < table->size - 1; ++i)
        for (size_t j = 0; j < table->size - i - 1; ++j)
            if (strcmp(table->keySet[j].authorSurname, table->keySet[j + 1].authorSurname))
            {
                Key temp = table->keySet[j];
                table->keySet[j] = table->keySet[j + 1];
                table->keySet[j + 1] = temp;
            }
}

void bsort_table_by_entries(Table *table)
{
    if (!table || table->size <= 1)
        return;

    for (size_t i = 0; i < table->size - 1; ++i)
        for (size_t j = 0; j < table->size - i - 1; ++j)
            if (strcmp(table->entrySet[j].authorSurname, table->entrySet[j + 1].authorSurname))
            {
                Book temp = table->entrySet[j];
                table->entrySet[j] = table->entrySet[j + 1];
                table->entrySet[j + 1] = temp;
            }
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
    if (!table || table->size <= 1)
        return;

    qsort(table->keySet, table->size, sizeof(Key), qcompare_keys);
}

void qsort_table_by_entries(Table *table)
{
    if (!table || table->size <= 1)
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
    for (size_t i = found_index; i + 1 < table->size; ++i)
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
                if (!found)
                {
                    print_table_header();
                }
                print_table_entry(table->entrySet + i);
                found = true;
            }
        }
    }

    if (found)
        print_table_splitter();

    return found ? SUCCESS : NOT_FOUND;
}

int print_key_array(Table *table)
{
    if (!table)
        return NULLPTR_ERROR;

    if (!table->size)
        return EMPTY_TABLE;

    print_key_table_header();
    for (size_t i = 0; i < table->size; ++i)
        print_key_table_entry(table->keySet + i);
    print_key_table_splitter();
    return SUCCESS;
}

int print_table_by_keys(Table *table)
{
    if (!table)
        return NULLPTR_ERROR;

    if (!table->size)
        return EMPTY_TABLE;

    print_table_header();
    for (size_t i = 0; i < table->size; ++i)
        print_table_entry(table->entrySet + table->keySet[i].index);
    print_table_splitter();
    return SUCCESS;
}

int print_table_by_entries(Table *table)
{
    if (!table)
        return NULLPTR_ERROR;

    if (!table->size)
        return EMPTY_TABLE;

    print_table_header();
    for (size_t i = 0; i < table->size; ++i)
        print_table_entry(table->entrySet + i);
    print_table_splitter();
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
