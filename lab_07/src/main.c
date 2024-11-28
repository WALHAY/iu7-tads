#include "../inc/AVLTree.h"
#include "../inc/BinaryTree.h"
#include "../inc/GraphvizIntegration.h"
#include "../inc/HashMap.h"
#include "../inc/LinkedHashMap.h"

static void printNode(TreeNode *node, void *param)
{
    printf("%d\n", node->value);
}

int main(void)
{
    // AVLTreeNode *root = NULL;
    // root = avlTreeInsert(root, 1);
    // root = avlTreeInsert(root, 2);
    // root = avlTreeInsert(root, 3);
    // root = avlTreeInsert(root, 4);
    // root = avlTreeInsert(root, 5);
    // root = avlTreeInsert(root, 6);
    // root = avlTreeInsert(root, 7);
    // treeDFS((TreeNode *)root, printNode, NULL);
    // drawGraph((TreeNode *)root, "nigga", true);
    //
    //
    // LinkedHashMap *hashMap = createHashMap(4);

    // linkedHashMapInsert(hashMap, "ab", 8);
    // linkedHashMapInsert(hashMap, "bb", 4);
    // linkedHashMapInsert(hashMap, "Hh", 1);
    // int value = 0;
    // if (linkedHashMapFind(hashMap, "Hi", &value))
    //     printf("Found: %d\n", value);
    // if (linkedHashMapFind(hashMap, "Hh", &value))
    //     printf("Found: %d\n", value);
    //
    HashMap *map = createHashMap(4);
    hashMapInsert(map, "Hi", 4);
    int value = 0;
    if (hashMapFind(map, "Hih", &value))
        printf("Found: %d\n", value);
    return 0;
}
