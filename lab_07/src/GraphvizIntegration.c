#include "../inc/GraphvizIntegration.h"

static size_t nullIndex = 0;

static void addSingleNode(TreeNode *from, TreeNode *to, FILE *stream)
{

    if (!to)
        fprintf(stream, "null%zu [shape=point];\n", nullIndex);
    fprintf(stream, "%d -> ", from->value);
    if (to)
    {
        fprintf(stream, "%d;\n", to->value);
    }
    else
        fprintf(stream, "null%zu;\n", nullIndex++);
}

static void addNodeToDot(TreeNode *node, void *stream)
{
    FILE *file = stream;

    addSingleNode(node, node->left, file);
    addSingleNode(node, node->right, file);
}

bool prepareGraph(TreeNode *head, const char *graphName, const char *path)
{
    if (!head || !graphName || !path)
        return false;
    FILE *graphFile = fopen(path, "w");

    if (!graphFile)
        return false;

    fprintf(graphFile,
            "digraph %s {\n"
            "node [shape=circle, fontname=\"Arial\", fontsize=12];\n"
            "edge [fontsize=10];\n",
            graphName);

    treeDFS(head, addNodeToDot, graphFile);

    fprintf(graphFile, "}\n");
    fclose(graphFile);
    return true;
}

void drawGraph(TreeNode *node, const char *filename, bool open)
{
    char path[strlen(filename) + 30];
    sprintf(path, "./out/%s.dot", filename);

    bool status = prepareGraph(node, filename, path);
    if (!status)
    {
        printf("Failed to prepare graph!\n");
        return;
    }

    char command[(strlen(filename) * 2 + 100)];
    sprintf(command, "dot -Tjpg %s -o ./img/%s.jpg", path, filename);

    system(command);
    if (open)
    {
        char openCmd[strlen(filename) * 2 + 100];
        sprintf(openCmd, "open ./img/%s.jpg", filename);
        system(openCmd);
    }
}
