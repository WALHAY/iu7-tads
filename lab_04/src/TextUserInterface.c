#include "TextUserInterface.h"

static int safeIntInput(int *value)
{
    char temp[20];
    fgets(temp, 20, stdin);
    char *end = NULL;
    errno = 0;
    long val = strtol(temp, &end, 10);
    if (errno == ERANGE || errno == EINVAL || end == temp)
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

uintptr_t inputAddress(char *title)
{
    void *ptr = NULL;
    printf("Enter %s: ", title);
    while (scanf("%p", &ptr) != 1)
        printf("Error: Wrong address!\n"
               "Enter %s again: ",
               title);
    fflush(stdin);
    return (uintptr_t)ptr;
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
        case EMPTY_STACK_POP:
            return "Error: Trying to pop element in empty stack!";
    }
    return "Error: No Error?";
}

int executeOperation(LinkedStack *linkedStack, ArrayStack *arrayStack)
{
    char *opts[] = {"Array Stack Push",
                    "Array Stack Pop",
                    "Linked Stack Push",
                    "Linked Stack Pop",
                    "Compare Array and Linked Stack",
                    "Print All Freed Memory",
                    "Exit"};
    size_t option = inputEnum(7, opts);
    printf("Executing: %s\n\n", opts[option]);
    int rc = SUCCESS;
    switch (option)
    {
        case ARR_PUSH:
            {
                uintptr_t ptr = inputAddress("random address in memory");
                pushArr(arrayStack, ptr, &rc);
                if (!rc)
                    printf("Element pushed (array stack): %p\n", (void *)ptr);
                return rc;
            }
        case ARR_POP:
            {
                uintptr_t ptr = popArr(arrayStack, &rc);
                if (!rc)
                    printf("Element popped (array stack): %p\n", (void *)ptr);
                return rc;
            }
        case LINKED_PUSH:
            {
                uintptr_t ptr = push(linkedStack, &rc);
                if (!rc)
                    printf("Element pushed (linked stack): %p\n", (void *)ptr);
                return rc;
            }
        case LINKED_POP:
            {
                uintptr_t ptr = pop(linkedStack, &rc);
                if (!rc)
                    printf("Element popped (linked stack): %p\n", (void *)ptr);
                return rc;
            }
            break;
        case PRINT_FREED:
            printf("Freed Memory:\n");
            printFreedMemory();
            break;
        case COMPARISON:
            compareTaDS(stdout);
            break;
        case EXIT:
            {
                destroyStack(linkedStack);
                destroyStackArr(arrayStack);
                exit(SUCCESS);
            }
    }
    return rc;
}
