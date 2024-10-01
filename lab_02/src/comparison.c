#include "../inc/comparison.h"

static void shuffle_table(Table *table)
{
    for (size_t i = 0; i < table->size; ++i)
        swap_entries(table->entrySet + i, table->entrySet + rand() % table->size);
    generate_key_array(table);
}

void get_time_efficiency_bsort(Table *table)
{
    struct timespec t1, t2;
    size_t entries_sum = 0;
    size_t keys_sum = 0;
    printf("Bubble Sort Comparison\n");
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
    printf("Bubble Sort entries: %zu ns\nBubble Sort keys: %zu ns\n", avg_entries, avg_keys);
}

void get_time_efficiency_qsort(Table *table)
{
    struct timespec t1, t2;
    size_t entries_sum = 0;
    size_t keys_sum = 0;
    printf("QSort Comparison\n");
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
    printf("QSort entries: %zu ns\nQSort keys: %zu ns\n", avg_entries, avg_keys);
}

void get_memory_efficiency(Table *table)
{
    size_t entries_size = sizeof(Book) * table->size;
    size_t keys_size = sizeof(Key) * table->size;
    long double sum = entries_size + keys_size;
    printf("Table with keys is bigger on %.2Lf%% = %zu bytes", sum / entries_size * 100.0f, keys_size);
}

void get_program_efficiency(void)
{
}
