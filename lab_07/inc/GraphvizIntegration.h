#pragma once

#include "AVLTree.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool prepareGraph(Node *node, const char *graphname, const char *path);

void drawGraph(Node *node, const char *filename, bool open);
