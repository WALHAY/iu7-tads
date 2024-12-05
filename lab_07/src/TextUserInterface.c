#include "../inc/TextUserInterface.h"

static char *findResult[2] = {"Not Found", "Found"};
static char *removeResult[2] = {"Not Found", "Removed"};

static int safeIntInput(int *value)
{
    char temp[20];
    fgets(temp, 19, stdin);
    char *end = NULL;
    errno = 0;
    long val = strtol(temp, &end, 10);
    if (errno == ERANGE || errno == EINVAL || end == temp || end - temp + 1 != (long)strlen(temp))
        return NAN_ERROR;
    *value = val;
    return SUCCESS;
}

size_t inputEnum(size_t max_options, char **options)
{
    printf("\nPossible variants:\n");
    for (size_t i = 0; i < max_options; ++i)
        printf("\t%zu. %s\n", i, options[i]);

    size_t option = 0;
    printf("Option: ");
    while (safeIntInput((int *)&option) || option >= max_options)
        printf("Error: Wrong option!\n"
               "Enter option again: ");
    return option;
}

int inputValue(char *title, bool min_limit, bool max_limit, int min_value, int max_value)
{
    int value = 0;
    printf("Enter %s: ", title);
    while (safeIntInput(&value) || (max_limit && value > max_value) || (min_limit && value < min_value))
        printf("Error: Wrong value!\n"
               "Enter %s again: ",
               title);
    return value;
}

char *inputString(char *title)
{
    char *temp = NULL;
    size_t size = 0;
    while (true)
    {
        temp = NULL;
        printf("Enter %s: ", title);
        if (getline(&temp, &size, stdin) == -1)
        {
            free(temp);
            continue;
        }

        temp[strcspn(temp, "\n")] = '\0';

        if (!temp || *temp == '\0')
            continue;
        break;
    }
    return temp;
}

char *getErrorMessage(int rc)
{
    return rc ? "Error: Unknown Error" : "";
}

int executeOperation(HashMap **hashMap, LinkedHashMap **linkedHashMap, AVLTreeNode **avlTree, TreeNode **node)
{
    char *opts[] = {"Import from file", "Create new structures", "Add value",  "Find value", "Remove value",
                    "Print hash maps",  "Draw graphs",           "Comparison", "Exit"};
    OPCODES option = inputEnum(9, opts);
    printf("Executing: %s\n", opts[option]);
    int rc = SUCCESS;
    switch (option)
    {
        case FROM_FILE:
            {
                FILE *file = NULL;
                char *filename = inputString("filename to import");
                if (filename && !file)
                    file = openFile(filename, "r");

                if (file)
                {
                    *hashMap = hashMapFromFile(file);
                    *linkedHashMap = linkedHashMapFromFile(file);
                    *avlTree = avlTreeFromFile(file);
                    *node = binaryTreeFromFile(file);
                }
                else
                    rc = IO_ERROR;
            }
            break;
        case NEW:
            if (hashMap)
                freeHashMap(hashMap);

            if (linkedHashMap)
                freeLinkedHashMap(linkedHashMap);

            if (node)
                treeFree(node);

            if (avlTree)
                avlTreeFree(avlTree);

            *hashMap = createHashMap(INITIAL_SIZE);
            *linkedHashMap = createLinkedHashMap(INITIAL_SIZE);
            break;
        case ADD:
            {
                int value = inputValue("value to insert", false, false, 0, 0);
                hashMapInsert(*hashMap, value);
                linkedHashMapInsert(*linkedHashMap, value);
                *avlTree = avlTreeInsert(*avlTree, value);
                *node = treeInsert(*node, value);
            }
            break;
        case FIND:
            {
                int value = inputValue("value to find", false, false, 0, 0);
                printf("Closed Hash Map: %s\n", findResult[hashMapFind(*hashMap, value)]);
                printf("Open Hash Map: %s\n", findResult[linkedHashMapFind(*linkedHashMap, value)]);
                printf("AVL Tree: %s\n", findResult[avlTreeFind(*avlTree, value) != NULL]);
                printf("Binary Search Tree: %s\n\n", findResult[treeFind(*node, value) != NULL]);
            }
            break;
        case REMOVE:
            {
                int value = inputValue("value to remove", false, false, 0, 0);
                printf("Closed Hash Map: %s\n", removeResult[hashMapRemove(*hashMap, value)]);
                printf("Open Hash Map: %s\n", removeResult[linkedHashMapRemove(*linkedHashMap, value)]);
                bool avlRemove = avlTreeFind(*avlTree, value);
                bool nodeRemove = treeFind(*node, value);
                *avlTree = avlTreeRemove(*avlTree, value);
                *node = treeRemove(*node, value);
                printf("AVL Tree: %s\n", removeResult[avlRemove]);
                printf("Binary Search Tree: %s\n\n", removeResult[nodeRemove]);
            }
            break;
        case PRINT:
            printf("Open Hash Map:\n");
            printLinkedHashMap(*linkedHashMap);
            printf("\nClosed Hash Map:\n");
            printHashMap(*hashMap);
            break;
        case DRAW_GRAPH:
            drawGraph(*node, "binaryTree", true);
            drawGraph((TreeNode *)*avlTree, "avlTree", true);
            break;
        case COMPARISON:
            compareTaDS();
            break;
        case EXIT:
        default:
            exit(SUCCESS);
    }
    return rc;
}
