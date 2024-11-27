#pragma once

#include "BinaryTree.h"
#include <stdbool.h>
#include <string.h>

bool prepareGraph(TreeNode *node, const char *graphname, const char *path);

void drawGraph(TreeNode *node, const char *filename, bool open);
