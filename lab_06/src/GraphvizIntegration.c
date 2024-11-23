#include "../inc/GraphvizIntegration.h"

static void addNodeToDot(TreeNode *node, void *steam)
{
    FILE *file = steam;

    if (node->left)
    {
        fprintf(file, "%s", node->data->name);
        fprintf(file, " -> ");
        fprintf(file, "%s", node->left->data->name);
        fprintf(file, ";\n");
    }

    if (node->right)
    {
        fprintf(file, "%s", node->data->name);
        fprintf(file, " -> ");
        fprintf(file, "%s [tooltip=%lf]", node->right->data->name, node->right->data->score);
        fprintf(file, ";\n");
    }
}

bool prepareGraph(TreeNode *head, const char *graphName, const char *path)
{
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

void drawGraph(TreeNode *node, const char *filename)
{
    char path[strlen(filename) + 30];
    sprintf(path, "./img/%s.dot", filename);

    bool status = prepareGraph(node, filename, path);
    if (!status)
    {
        printf("Failed to prepare graph!\n");
        return;
    }

    char command[(strlen(filename) * 2 + 100)];
    sprintf(command, "dot -Tsvg %s -o ./img/output_%s.svg && inkview ./img/output_%s.svg", path, filename, filename);

    system(command);
}
