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

    // LinkedHashMap *hashMap = createLinkedHashMap(2);

    // linkedHashMapInsert(hashMap, "a", 8);
    // printf("size %zu\n", hashMap->size);
    // linkedHashMapInsert(hashMap, "b", 8);
    // printf("size %zu\n", hashMap->size);
    // linkedHashMapInsert(hashMap, "c", 8);
    // printf("size %zu\n", hashMap->size);
    // linkedHashMapInsert(hashMap, "d", 8);
    // printf("size %zu\n", hashMap->size);
    // linkedHashMapInsert(hashMap, "e", 8);
    // printf("size %zu\n", hashMap->size);

    HashMap *map = createHashMap(10);
    hashMapInsert(map, "a", 1);
    printf("size %zu\n", map->size);
    hashMapInsert(map, "b", 1);
    printf("size %zu\n", map->size);
    hashMapInsert(map, "c", 1);
    printf("size %zu\n", map->size);
    hashMapInsert(map, "d", 1);
    printf("size %zu\n", map->size);
    hashMapInsert(map, "e", 1);
    printf("size %zu\n", map->size);
    hashMapInsert(map, "f", 1);
    printf("size %zu\n", map->size);
    hashMapInsert(map, "g", 1);
    printf("size %zu\n", map->size);
    hashMapInsert(map, "h", 1);
    printf("size %zu\n", map->size);
    return 0;
}
