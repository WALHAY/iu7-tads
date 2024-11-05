#include "../inc/TextUserInterface.h"

static int requests = 1000;
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

static int safeFloatInput(float *value)
{
    char temp[20];
    fgets(temp, 19, stdin);
    char *end = NULL;
    errno = 0;
    float val = strtof(temp, &end);
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

float inputValue(char *title, bool min_limit, bool max_limit, float min_value, float max_value)
{
    float value = 0;
    printf("Enter %s: ", title);
    while (safeFloatInput(&value) || (max_limit && value > max_value) || (min_limit && value < min_value))
        printf("Error: Wrong value!\n"
               "Enter %s again: ",
               title);
    return value;
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

void inputTimeSpecification(TimeSpecification *timings)
{
    timings->firstMin = inputValue("First queue enter min time", true, false, 0, 0);
    timings->firstMax = inputValue("First queue enter max time", true, false, 0, 0);

    timings->secondMin = inputValue("Second queue enter min time", true, false, 0, 0);
    timings->secondMax = inputValue("Second queue enter max time", true, false, 0, 0);

    timings->oaFirstMin = inputValue("First queue request process min time", true, false, 0, 0);
    timings->oaFirstMax = inputValue("First queue request process max time", true, false, 0, 0);

    timings->oaSecondMin = inputValue("Second queue request process min time", true, false, 0, 0);
    timings->oaSecondMax = inputValue("Second queue request process max time", true, false, 0, 0);
}

void printCurrentTimings(void)
{
    printf("--- Current timings ---\n");
    printf("First queue enter min time: %.2f\n", timings.firstMin);
    printf("First queue enter max time: %.2f\n", timings.firstMax);

    printf("Second queue enter min time: %.2f\n", timings.secondMin);
    printf("Second queue enter max time: %.2f\n", timings.secondMax);

    printf("First queue request process min time: %.2f\n", timings.oaFirstMin);
    printf("First queue request process max time: %.2f\n", timings.oaFirstMax);

    printf("Second queue request process min time: %.2f\n",timings.oaSecondMin);
    printf("Second queue request process max time: %.2f\n\n",timings.oaSecondMax);
}

int executeOperation(void)
{
    char *opts[] = {"Change requests", "Change timings", "Simulate 1000 requests : Array Queue ", "Simulate 1000 requests : Linked Queue ",
                    "Compare Array and Linked Queue", "Print All Freed Memory", "Exit"};
    OPCODES option = inputEnum(7, opts);
    printf("Executing: %s\n\n", opts[option]);
    int rc = SUCCESS;
    switch (option)
    {
        case CHANGE_REQUESTS:
            requests = inputValue("first type requests amount", true, false, 0, 0);
            break;
        case CHANGE_TIMINGS:
            printCurrentTimings();
            inputTimeSpecification(&timings);
            break;
        case SIMULATE_ARR:
            taskArray(requests, &timings);
            break;
        case SIMULATE_LINKED:
            task(requests, &timings);
            break;
        case COMPARE_TADS:
            clearFreedMemory();
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
