#include "../inc/TextUserInterface.h"

static size_t graphIndex = 0;

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
    return "Error: No Error?";
}

static void executeLinkedHashMapOperation(LinkedHashMap **linkedHashMap)
{
    bool exit = false;
    while (!exit)
    {
        char *opts[] = {"New Open Hash Map", "Add Element", "Find Element", "Print Hash Map", "Back"};
        HASHMAP_OPS option = inputEnum(5, opts);
        printf("Open Hash Map: %s\n", opts[option]);
        switch (option)
        {
            case NEW:
                if (linkedHashMap)
                {
                    if (*linkedHashMap)
                        freeLinkedHashMap(linkedHashMap);
                    *linkedHashMap = createLinkedHashMap(INITIAL_SIZE);
                }
                break;
            case ADD:
                if (linkedHashMap && *linkedHashMap)
                {
                    char *key = inputString("key");
                    int value = inputValue("value", false, false, 0, 0);
                    linkedHashMapInsert(*linkedHashMap, key, value);
                }
                else
                    printf("Error: Create hash map first!\n");
                break;

            case FIND:
                {
                    char *key = inputString("key to find");
                    int value = 0;
                    if (linkedHashMapFind(*linkedHashMap, key, &value))
                        printf("Value: %d\n", value);
                    else
                        printf("Key not found!\n");
                }
                break;
            case PRINT:
                printLinkedHashMap(*linkedHashMap);
                break;
            case MAP_BACK:
            default:
                exit = true;
        }
    }
}

static int executeHashMapOperation(HashMap **hashMap)
{
    bool exit = false;
    while (!exit)
    {
        char *opts[] = {"New Open Hash Map", "Add Element", "Find Element", "Print Hash Map", "Back"};
        HASHMAP_OPS option = inputEnum(5, opts);
        printf("Open Hash Map: %s\n", opts[option]);
        switch (option)
        {
            case NEW:
                if (hashMap)
                {
                    if (*hashMap)
                        freeHashMap(hashMap);
                    *hashMap = createHashMap(INITIAL_SIZE);
                }
                break;
            case ADD:
                if (hashMap && *hashMap)
                {
                    char *key = inputString("key");
                    int value = inputValue("value", false, false, 0, 0);
                    hashMapInsert(*hashMap, key, value);
                }
                else
                    printf("Error: Create hash map first!\n");
                break;

            case FIND:
                {
                    char *key = inputString("key to find");
                    int value = 0;
                    if (hashMapFind(*hashMap, key, &value))
                        printf("Value: %d\n", value);
                    else
                        printf("Key not found!\n");
                }
                break;
            case PRINT:
                printHashMap(*hashMap);
                break;
            case MAP_BACK:
            default:
                exit = true;
        }
    }
}

static int executeBinaryTreeOperation(TreeNode **binTree)
{
    bool exit = false;
    while (!exit)
    {
    }
    return 0;
}

static int executeAvlTreeOperation(AVLTreeNode **avlTree)
{
    bool exit = false;
    while (!exit)
    {
    }
    return 0;
}

int executeOperation(HashMap **hashMap, LinkedHashMap **linkedHashMap, AVLTreeNode **avlTree, TreeNode **node)
{
    char *opts[] = {"Closed Hash Map", "Open Hash Map", "AVL Tree", "Binary Search Tree", "Comparison", "Exit"};
    OPCODES option = inputEnum(6, opts);
    printf("Executing: %s\n", opts[option]);
    int rc = SUCCESS;
    switch (option)
    {
        case CLOSED_HASH_MAP:
            executeHashMapOperation(hashMap);
            break;
        case OPEN_HASH_MAP:
            executeLinkedHashMapOperation(linkedHashMap);
            break;
        case AVL_TREE:
            executeAvlTreeOperation(avlTree);
            break;
        case BIN_TREE:
            executeBinaryTreeOperation(node);
            break;
        case EXIT:
        default:
            exit(SUCCESS);
    }
    return rc;
}
