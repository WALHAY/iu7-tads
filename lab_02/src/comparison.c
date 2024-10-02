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
    printf("Bubble Sort Comparison(average of %d tries)\n", TRIES);
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
    printf("Bubble Sort entries:\t%zu ns\nBubble Sort keys:\t%zu ns\n", avg_entries, avg_keys);
}

void get_time_efficiency_qsort(Table *table)
{
    struct timespec t1, t2;
    size_t entries_sum = 0;
    size_t keys_sum = 0;
    printf("QSort Time Comparison(average of %d tries)\n", TRIES);
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
    printf("QSort entries:\t%zu ns\nQSort keys:\t%zu ns\n", avg_entries, avg_keys);
}

void get_memory_efficiency(void)
{
    size_t entry_size = sizeof(Book);
    size_t key_size = sizeof(Key);
    long double sum = entry_size + key_size;
    printf("\nKey array size of all size is %.2Lf%%\n", key_size / sum * 100.0f);
}

void get_program_efficiency(void)
{
    for (size_t i = 50; i <= 500; i += 50)
    {
        Table table = {.size = 0};
        printf("\nElement count: %zu\n", i);
        generate_entries(&table, i);
        get_time_efficiency_bsort(&table);
        printf("\n");
        get_time_efficiency_qsort(&table);
    }
    get_memory_efficiency();
}
