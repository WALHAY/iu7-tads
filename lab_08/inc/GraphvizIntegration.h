#pragma once

#include "Graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void drawGraph(const Graph *graph, const char *name);

void drawGraphWithPath(const Graph *graph, const Path *path, const char *name);
