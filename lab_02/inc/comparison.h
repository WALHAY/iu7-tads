#pragma once

#include "entry_generator.h"
#include "table.h"
#include "tui.h"
#include <stdlib.h>
#include <time.h>

#define TRIES 50

void get_time_efficiency_bsort(Table *table, FILE *file, size_t size);

void get_time_efficiency_qsort(Table *table, FILE *file, size_t size);

void get_memory_efficiency(void);

void get_program_efficiency(void);
