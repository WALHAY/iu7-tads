#include "../inc/TextUserInterface.h"

static size_t graphIndex = 0;

static bool lowScoreFilter(const TreeNode *node)
{
    return node->data->score > 2;
}

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

StudentData *inputStudentData(int *rc)
{
    char *surname = inputString("student surname");
    float score = inputValue("student score", 1, 1, 0, 5);
    return createData(surname, score, rc);
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
        case EMPTY_GRAPH:
            return "Error: Tree is empty!";
    }
    return "Error: No Error?";
}

void printNode(TreeNode *node, void *param)
{
    if (param)
        return;
    StudentData *data = node->data;
    printf("%s %f\n", data->name, data->score);
}

int executeOperation(TreeNode **head_ptr)
{
    TreeNode *head = *head_ptr;
    char *opts[] = {"Add student", "Find Student",     "Remove Student", "Print Tree",
                    "Draw Graph",  "Remove Low Score", "Compare TaDS",   "Exit"};
    OPCODES option = inputEnum(8, opts);
    printf("Executing: %s\n", opts[option]);
    int rc = SUCCESS;
    switch (option)
    {
        case ADD:
            *head_ptr = treeInsert(head, inputStudentData(&rc), surnameComparator, &rc);
            break;
        case FIND:
            {
                char *prefix = inputString("surname prefix");
                TreeNode *node = treeFind(head, prefix);
                if (node)
                    printStudent(node->data);
                else
                    printf("Student not found!\n");
                break;
            }
        case REMOVE:
            {
                char *prefix = inputString("surname prefix");
                *head_ptr = treeRemove(head, prefix);
                break;
            }
            break;
        case PRINT:
            if (!head)
                return EMPTY_GRAPH;
            depthFirstSearch(head, printNode, NULL);
            break;
        case SHOW_GRAPH:
            if (!head)
                return EMPTY_GRAPH;
            char graphName[255];
            sprintf(graphName, "BST_%zu", graphIndex++);
            drawGraph(head, graphName, true);
            break;
        case REMOVE_LOW:
            *head_ptr = filterTree(head, lowScoreFilter);
            break;
        case COMPARE_TADS:
            compareTaDS(stdout);
            break;
        case EXIT:
            exit(SUCCESS);
    }
    return rc;
}
