#pragma once

#include "AVLTree.h"
#include "BinaryTree.h"
#include "Defines.h"
#include "HashMap.h"
#include "LinkedHashMap.h"

FILE *openFile(const char *filename, const char *mode);

void closeFile(FILE **file);

LinkedHashMap *linkedHashMapFromFile(FILE *file);

HashMap *hashMapFromFile(FILE *file);

AVLTreeNode *avlTreeFromFile(FILE *file);

TreeNode *binaryTreeFromFile(FILE *file);
