#include "../inc/GraphvizIntegration.h"
#include <unistd.h>

void drawGraph(const Graph *graph, const char *name)
{
    FILE *graphFile = fopen("./out/graph.dot", "w");
    fprintf(graphFile, "digraph %s {\n", name);
    // fprintf(graphFile, "edge [color=red];");

    for (size_t i = 0; i < graph->size; ++i)
    {
        bool zeroEdgeVertex = true;
        for (size_t j = 0; j < graph->size; ++j)
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
    FILE *graphFile = fopen("./out/graph.dot", "w");
    fprintf(graphFile, "digraph %s {\n", name);

    for (size_t i = 0; i < graph->size; ++i)
    {
        bool zeroEdgeVertex = true;
        for (size_t j = 0; j < graph->size; ++j)
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
    system("dot -Tjpg ./out/graph.dot -o ./img/graph.jpg");
    if (false)
        printf("Failed to draw graph!\n");
    else
        system("open ./img/graph.jpg");
}
