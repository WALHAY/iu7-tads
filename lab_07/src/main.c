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
    LinkedHashMap *hashMap = createLinkedHashMap(2);

    linkedHashMapInsert(hashMap, "a", 8);
    printf("size %zu\n", hashMap->size);
    linkedHashMapInsert(hashMap, "b", 8);
    printf("size %zu\n", hashMap->size);
    linkedHashMapInsert(hashMap, "c", 8);
    printf("size %zu\n", hashMap->size);
    linkedHashMapInsert(hashMap, "d", 8);
    printf("size %zu\n", hashMap->size);
    linkedHashMapInsert(hashMap, "e", 8);
    printf("size %zu\n", hashMap->size);

    // HashMap *map = createHashMap(4);
    // hashMapInsert(map, "Hi", 4);
    // int value = 0;
    // if (hashMapFind(map, "Hih", &value))
    //     printf("Found: %d\n", value);
    return 0;
}
