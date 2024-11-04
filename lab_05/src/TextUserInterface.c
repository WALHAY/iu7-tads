#include "../inc/TextUserInterface.h"

#define REQUESTS 1000

static TimeSpecification timings = {1, 5, 0, 3, 0, 4, 0, 1};

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

char *getErrorMessage(int rc)
{
    switch (rc)
    {
        case NULLPTR_ERROR:
            return "Error: Null pointer passed to function!";
        case ALLOC_ERROR:
            return "Error: Failed to allocate memory!";
        case NAN_ERROR:
            return "Error: Not A Number!";
        case EMPTY_QUEUE_POP:
            return "Error: Trying to pop element in empty queue!";
    }
    return "Error: No Error?";
}

int executeOperation(void)
{
    char *opts[] = {"Simulate 1000 requests : Array Queue ", "Simulate 1000 requests : Linked Queue ",
                    "Compare Array and Linked Queue", "Print All Freed Memory", "Exit"};
    OPCODES option = inputEnum(5, opts);
    printf("Executing: %s\n\n", opts[option]);
    int rc = SUCCESS;
    switch (option)
    {
        case SIMULATE_ARR:
            taskArray(REQUESTS, &timings);
            break;
        case SIMULATE_LINKED:
            task(REQUESTS, &timings);
            break;
        case COMPARE_TADS:
            compareTaDS(stdout);
            break;
        case PRINT_FREED:
            printFreedMemory();
            break;
        case EXIT:
            exit(SUCCESS);
    }
    return rc;
}
