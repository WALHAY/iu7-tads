#include "../inc/TextUserInterface.h"

Graph *graph = NULL;

static int safeIntInput(int *value)
{
    char temp[20];
    fgets(temp, 19, stdin);
    char *end = NULL;
    errno = 0;
    long val = strtol(temp, &end, 10);
    if (errno == ERANGE || errno == EINVAL || end == temp || end - temp + 1 != (long)strlen(temp))
        return 1;
    *value = val;
    return 0;
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

void executeOperation(void)
{
    char *opts[] = {"Create new graph",         "Add edge",         "Remove edge", "Draw graph",
                    "Find common longest path", "Import from file", "Exit"};
    OPCODES option = inputEnum(7, opts);
    printf("Executing: %s\n", opts[option]);
    switch (option)
    {
        case NEW:
            {
                int value = inputValue("vertices count", true, false, 0, 0);

                graph = createGraph(value);
            }
            break;
        case ADD_EDGE:
            {
                if (!graph)
                {
                    printf("Create graph first!\n");
                    return;
                }

                printf("Input vertices to add edge between\n");
                int first = inputValue("first vertex", true, true, 0, graph->size - 1);
                int second = inputValue("second vertex", true, true, 0, graph->size - 1);
                addEdge(graph, first, second);
            }
            break;
        case REMOVE_EDGE:
            {
                if (!graph)
                {
                    printf("Create graph first!\n");
                    return;
                }

                printf("Input vertices to remove edge between\n");
                int first = inputValue("first vertex", true, true, 0, graph->size - 1);
                int second = inputValue("second vertex", true, true, 0, graph->size - 1);
                removeEdge(graph, first, second);
            }
            break;
        case DRAW:
            {
                if (!graph)
                {
                    printf("Create graph first!\n");
                    return;
                }

                drawGraph(graph, "simple");
            }
            break;
        case FIND_PATH:
            {

                if (!graph)
                {
                    printf("Create graph first!\n");
                    return;
                }

                Path result = {0};
                findMaxSimplePath(graph, &result);

                for (size_t i = 0; i < result.size; ++i)
                    printf("%d\n", result.path[i]);

                drawGraphWithPath(graph, &result, "path");
            }
            break;
        case FROM_FILE:
            {
                char *filename = inputString("file to import graph");
                if (!filename)
                {
                    printf("Wrong filename!\n");
                    return;
                }

                FILE *file = fopen(filename, "r");
                if (!file)
                {
                    printf("Cant open file!\n");
                    return;
                }

                graph = importFromFile(file);
            }
            break;
        case EXIT:
        default:
            exit(0);
    }
}
