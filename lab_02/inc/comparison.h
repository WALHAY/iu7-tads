#pragma once

#include "entry_generator.h"
#include "table.h"
#include <time.h>

#define TRIES 50

void get_time_efficiency_bsort(Table *table);

void get_time_efficiency_qsort(Table *table);

void get_memory_efficiency(Table *table);

void get_program_efficiency(void);
