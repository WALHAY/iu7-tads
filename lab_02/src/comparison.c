#include "../inc/comparison.h"

static void print_table_splitter(void)
{
    printf("+");
    print_char_i_times('-', MAX_OUT_ELEMENT_WIDTH + 2);
    printf("+");
    print_char_i_times('-', MAX_OUT_TIME_WIDTH + 2);
    printf("+");
    print_char_i_times('-', MAX_OUT_TIME_WIDTH + 2);
    printf("+\n");
}

static void print_table_header(void)
{
    print_table_splitter();
    print_column("Elements", MAX_OUT_ELEMENT_WIDTH);
    print_column("Keys", MAX_OUT_TIME_WIDTH);
    print_column("Entries", MAX_OUT_TIME_WIDTH);
    printf("|\n");
    print_table_splitter();
}

static void print_table_entry(size_t elements, size_t keys, size_t entries)
{
    char elements_str[MAX_OUT_ELEMENT_WIDTH];
    sprintf(elements_str, "%zu", elements);
    print_column(elements_str, MAX_OUT_ELEMENT_WIDTH);
    char keys_time[MAX_OUT_TIME_WIDTH];
    sprintf(keys_time, "%zu", keys);
    print_column(keys_time, MAX_OUT_TIME_WIDTH);
    char entries_time[MAX_OUT_TIME_WIDTH];
    sprintf(entries_time, "%zu", entries);
    print_column(entries_time, MAX_OUT_TIME_WIDTH);
    printf("|\n");
}

static void shuffle_table(Table *table)
{
    for (size_t i = 0; i < table->size; ++i)
        swap_entries(table->entrySet + i, table->entrySet + rand() % table->size);
    generate_key_array(table);
}

void get_time_efficiency_bsort(Table *table, FILE *file, size_t size)
{
    struct timespec t1, t2;
    size_t entries_sum = 0;
    size_t keys_sum = 0;
    for (size_t i = 0; i < TRIES; ++i)
    {
        shuffle_table(table);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        bsort_table_by_entries(table);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        entries_sum += 1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec);

        shuffle_table(table);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        bsort_table_by_keys(table);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        keys_sum += 1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    size_t avg_entries = entries_sum / TRIES;
    size_t avg_keys = keys_sum / TRIES;
    print_table_entry(size, avg_keys, avg_entries);
    fprintf(file, "%zu %zu\n", avg_keys, avg_entries);
}

void get_time_efficiency_qsort(Table *table, FILE *file, size_t size)
{
    struct timespec t1, t2;
    size_t entries_sum = 0;
    size_t keys_sum = 0;
    for (size_t i = 0; i < TRIES; ++i)
    {
        shuffle_table(table);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        qsort_table_by_entries(table);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        entries_sum += 1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec);

        shuffle_table(table);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        qsort_table_by_keys(table);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        keys_sum += 1000000000 * difftime(t2.tv_sec, t1.tv_sec) + difftime(t2.tv_nsec, t1.tv_nsec);
    }
    size_t avg_entries = entries_sum / TRIES;
    size_t avg_keys = keys_sum / TRIES;
    print_table_entry(size, avg_keys, avg_entries);
    fprintf(file, "%zu %zu\n", avg_keys, avg_entries);
}

void get_memory_efficiency(void)
{
    size_t entry_size = sizeof(Book);
    size_t key_size = sizeof(Key);
    long double sum = entry_size + key_size;
    printf("\nKey array size to all size is %.2Lf%%\n", key_size / sum * 100.0f);
}

void get_program_efficiency(void)
{
    int rc = SUCCESS;
    FILE *file = open_file("comparison.txt", "w", &rc);
    printf("\n\nBubble Sort time efficiency\n");
    fprintf(file, "Bubble Sort time efficiency\n");
    print_table_header();
    for (size_t i = 50; i <= 500; i += 50)
    {
        Table table = {.size = 0};
        generate_entries(&table, i);
        get_time_efficiency_bsort(&table, file, i);
    }
    print_table_splitter();

    printf("\n\nQSort time efficiency\n");
    fprintf(file, "QSort time efficiency\n");
    print_table_header();
    for (size_t i = 50; i <= 500; i += 50)
    {
        Table table = {.size = 0};
        generate_entries(&table, i);
        get_time_efficiency_qsort(&table, file, i);
    }
    print_table_splitter();
    get_memory_efficiency();
}
