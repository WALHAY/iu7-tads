#include "../inc/TextUserInterface.h"

int main(void)
{
    HashMap *hashMap = createHashMap(INITIAL_SIZE);
    LinkedHashMap *linkedHashMap = createLinkedHashMap(INITIAL_SIZE);
    AVLTreeNode *avlTree = NULL;
    TreeNode *node = NULL;

    while (true)
    {
        int rc = executeOperation(&hashMap, &linkedHashMap, &avlTree, &node);
        if (rc)
            printf("%s\n", getErrorMessage(rc));
    }
    return 0;
}
