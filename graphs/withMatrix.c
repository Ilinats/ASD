#include <stdio.h>
#include <stdlib.h>

typedef struct Graph
{
    int numVertices;
    int **adjMatrix;
} Graph;

Graph *init_graph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjMatrix = (int **)malloc(numVertices * sizeof(int *));

    for (int i = 0; i < numVertices; i++)
    {
        graph->adjMatrix[i] = (int *)calloc(numVertices, sizeof(int));
    }

    return graph;
}

void addEdgeDirectional(Graph *graph, int from, int to)
{
    if (from < 0 || from >= graph->numVertices || to < 0 || to >= graph->numVertices)
    {
        printf("Invalid from or to\n");
        return;
    }

    graph->adjMatrix[from][to] = 1;
}

void addEdge(Graph *graph, int from, int to)
{
    addEdgeDirectional(graph, from, to);
    addEdgeDirectional(graph, to, from);
}

void printGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void BFS(Graph* G) {
    Dlist *queue = initDlist();
    insertBegin(queue, 0);

    int* visited = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    int* parentNode = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    int* dist = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    visited[0] = 1;

    while(queue->head) {
        int current = pop(queue);
        printf("%d ", current);

        Node* currentNode = G->adjList[current];
        for(int i = 0; i < G->numVertices; i++) {
            if(G->adjMatrix[current][i] && !visited[i]) {
                insertBegin(queue, i);
                parentNode[i] = current;
                dist[i] = dist[current] + 1;
                visited[i] = 1;
            }
        }
    }
}

int main()
{
    Graph *graph = init_graph(4);
    addEdge(graph, 1, 2);
    addEdgeDirectional(graph, 2, 4);
    addEdgeDirectional(graph, 3, 4);
    addEdgeDirectional(graph, 2, 3);
    addEdgeDirectional(graph, 1, 3);
    addEdgeDirectional(graph, 1, 1);

    printGraph(graph);

    return 0;
}