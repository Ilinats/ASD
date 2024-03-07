#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int numVertices;
    int **adjMatrix;
} Graph;

Graph *init_graph(int numVertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjMatrix = (int **)malloc(numVertices * sizeof(int *));

    for (int i = 0; i < numVertices; i++)
        graph->adjMatrix[i] = (int *)calloc(numVertices, sizeof(int));

    return graph;
}

void addEdgeDirectional(Graph *graph, int from, int to) {
    if (from < 0 || from >= graph->numVertices || to < 0 || to >= graph->numVertices) {
        printf("Invalid from or to\n");
        return;
    }

    graph->adjMatrix[from][to] = 1;
}

void addEdge(Graph *graph, int from, int to) {
    addEdgeDirectional(graph, from, to);
    addEdgeDirectional(graph, to, from);
}

void printGraph(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++)
            printf("%d ", graph->adjMatrix[i][j]);

        printf("\n");
    }
}

int isThereUniversalSink(Graph* g) {
    int flag = 0;
    int noNext = -1;

    for(int i = 0; i < g->numVertices; i++) {
        for(int j = 0; j < g->numVertices; j++) {
            if(g->adjMatrix[i][j]) {
                flag = 1;
                break;
            }
        }

        if(flag == 0) {
            noNext = i;
            break;
        }
    }

    for(int i = 0; i < g->numVertices; i++) {
        if(i == noNext)
            continue;

        if(!g->adjMatrix[i][noNext])
            return 0;
    }

    if(noNext == -1)
        return 0;

    return 1;
}

int main() {
    Graph *graph = init_graph(4);
    addEdge(graph, 0, 1);
    addEdgeDirectional(graph, 1, 3);
    addEdgeDirectional(graph, 2, 3);
    addEdgeDirectional(graph, 1, 2);
    addEdgeDirectional(graph, 0, 2);
    addEdgeDirectional(graph, 0, 0);

    printGraph(graph);
    printf("\n");
    printf("%d\n", isThereUniversalSink(graph));

    Graph* g = init_graph(4);
    addEdge(g, 1, 2);
    addEdgeDirectional(g, 1, 0);
    addEdgeDirectional(g, 2, 0);
    addEdgeDirectional(g, 3, 0);
    addEdge(g, 2, 3);
    printf("%d\n", isThereUniversalSink(g));

    return 0;
}