#include "../inc/GraphvizIntegration.h"

static size_t nullIndex = 0;

static void addSingleNode(Node *from, Node *to, FILE *stream)
{

    if (!to)
        fprintf(stream, "null%zu [shape=point];\n", nullIndex);
    fprintf(stream, "%d -> ", from->value);
    if (to)
        fprintf(stream, "%d;\n", to->value);
    else
        fprintf(stream, "null%zu;\n", nullIndex++);
}

static void addNodeToDot(Node *node, void *stream)
{
    FILE *file = stream;

    addSingleNode(node, node->left, file);
    addSingleNode(node, node->right, file);
}

bool prepareGraph(Node *head, const char *graphName, const char *path)
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

    depthFirstSearch(head, addNodeToDot, graphFile);

    fprintf(graphFile, "}\n");
    fclose(graphFile);
    return true;
}

void drawGraph(Node *node, const char *filename, bool open)
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
    sprintf(command, "dot -Tsvg %s -o ./img/%s.svg", path, filename);
    if (open)
    {
        char openCmd[strlen(filename) * 2 + 100];
        sprintf(openCmd, "inkview ./img/%s.svg", filename);
        system(openCmd);
    }

    system(command);
}
