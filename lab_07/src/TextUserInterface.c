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

int executeHashMapOperation(HashMap **hashMap)
{
    return 0;
}

int executeOperation()
{
    char *opts[] = {"Closed Hash Map", "Open Hash Map", "AVL Tree", "Binary Search Tree", "Exit"};
    OPCODES option = inputEnum(5, opts);
    printf("Executing: %s\n", opts[option]);
    int rc = SUCCESS;
    switch (option)
    {
        case EXIT:
        default:
            exit(SUCCESS);
    }
    return rc;
}
