#include "../inc/TextUserInterface.h"

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

void executeOperation(LinkedStack *linkedStack, ArrayStack *arrayStack)
{
    char *opts[] = {"Array Stack Push",
                    "Array Stack Pop",
                    "Linked Stack Push",
                    "Linked Stack Pop",
                    "Compare Array and Linked Stack",
                    "Exit"};
    size_t option = inputEnum(6, opts);
    printf("Executing: %s\n\n", opts[option]);
    switch (option)
    {
        case ARR_PUSH:
            {
                push_arr(arrayStack, (uintptr_t)NULL);
            }
            break;
        case ARR_POP:
            {
                uintptr_t ptr = pop_arr(arrayStack);
                printf("Element popped(array stack): %p\n", (void *)ptr);
            }
            break;
        case LINKED_PUSH:
            {
                uintptr_t ptr = push(linkedStack);
                printf("Element pushed(linked stack): %p\n", (void *)ptr);
            }
            break;
        case LINKED_POP:
            {
                uintptr_t ptr = pop(linkedStack);
                printf("Element popped(linked stack): %p\n", (void *)ptr);
            }
            break;
        case COMPARISON:
            break;
        case EXIT:
            break;
    }
}
