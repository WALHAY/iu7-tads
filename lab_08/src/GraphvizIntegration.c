#include "../inc/GraphvizIntegration.h"
#include <unistd.h>

void drawGraph(const Graph *graph, const char *name)
{
    if (!graph || !name || !graph->size)
    {
        printf("Failed to draw graph!");
        return;
    }

    FILE *graphFile = fopen("./out/graph.dot", "w");
    fprintf(graphFile, "digraph %s {\n", name);
    fprintf(graphFile, "edge [arrowhead=none];\n");

    for (size_t i = 0; i < graph->size - 1; ++i)
    {
        bool zeroEdgeVertex = true;
        for (size_t j = i + 1; j < graph->size; ++j)
        {
            if (graph->matrix[i][j] != 0)
            {
                zeroEdgeVertex = false;
                fprintf(graphFile, "%zu -> %zu;\n", i, j);
            }
        }

        if (zeroEdgeVertex)
            fprintf(graphFile, "%zu;\n", i + 1);
    }

    fprintf(graphFile, "}\n");
    fclose(graphFile);

    system("dot -Tjpg ./out/graph.dot -o ./img/graph.jpg");
    system("open ./img/graph.jpg");
}

void drawGraphWithPath(const Graph *graph, const Path *path, const char *name)
{
    if (!graph || !path || !name || !graph->size)
    {
        printf("Failed to draw graph!");
        return;
    }

    FILE *graphFile = fopen("./out/path.dot", "w");
    fprintf(graphFile, "digraph %s {\n", name);
    fprintf(graphFile, "edge [arrowhead=none];\n");

    for (size_t i = 0; i < graph->size - 1; ++i)
    {
        bool zeroEdgeVertex = true;
        for (size_t j = i + 1; j < graph->size; ++j)
        {
            bool color = false;
            bool skip = false;
            for (size_t k = 0; k < path->size - 1; ++k)
            {
                if ((path->path[k] == i && path->path[k + 1] == j) || (path->path[k] == j && path->path[k + 1] == i))
                {
                    zeroEdgeVertex = false;
                    skip = true;
                }
            }

            if (!skip && graph->matrix[i][j] != 0)
            {
                zeroEdgeVertex = false;
                fprintf(graphFile, "%zu -> %zu;\n", i, j);
            }
        }

        if (zeroEdgeVertex)
            fprintf(graphFile, "%zu;\n", i + 1);
    }

    fprintf(graphFile, "edge [color=red];\n");
    for (size_t i = 0; i < path->size - 1; ++i)
        fprintf(graphFile, "%d -> %d;\n", path->path[i], path->path[i + 1]);

    fprintf(graphFile, "}\n");
    fclose(graphFile);

    system("dot -Tjpg ./out/path.dot -o ./img/path.jpg");
    system("open ./img/path.jpg");
}
