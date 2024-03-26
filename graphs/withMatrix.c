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

int is_euler(Graph* g) {
    int oddDegree = 0;

    for(int i = 0; i < g->numVertices; i++) {
        int numNeighbors = 0;
        for(int j = 0; j < g->numVertices; j++) {
            if(g->adjMatrix[i][j])
                numNeighbors++;
        }

        if(numNeighbors % 2)
            oddDegree++;
    }

    return oddDegree == 0 || oddDegree == 2;
}

void findEulerPath(Graph* g, int start) {
    printf("%d", start);

    for(int i = 0; i < g->numVertices; i++) {
        if(g->adjMatrix[start][i]) {
            g->adjMatrix[start][i] = 0;
            g->adjMatrix[i][start] = 0;
            findEulerPath(g, i);
        }
    }

}

int isHamiltonR(Graph* g, int start, int* visited, int visitedCount) {
     if(visitedCount == g->numVertices)
        return 1;

    for(int i = 0; i < g->numVertices; i++) {
        if(g->adjMatrix[start][i] && !visited[i]) {
            visited[i] = 1;
            visitedCount++;
            if(isHamiltonR(g, i, visited, visitedCount))
                return 1;
            visited[i] = 0;
            visitedCount--;
        }
    }
}

int isHamiltonian(Graph* g) {
    int visitedCount = 1;
    int* visited = (int*)calloc(g->numVertices, sizeof(int));
    int start = 0;

    isHamiltonR(g, start, visited, visitedCount);
}

int isSafe(int **graph, int path[], int pos, int v) {
    if (graph[path[pos - 1]][v] == 0)
        return 0;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

int isHamiltonianCycle(int **graph, int numVertices, int path[], int pos) {
    if (pos == numVertices) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return 1;
        else
            return 0;
    }

    for (int v = 0; v < numVertices; v++) {
        if (isSafe(graph, path, pos, v)) {
            path[pos] = v;

            if (isHamiltonianCycle(graph, numVertices, path, pos + 1))
                return 1;

            path[pos] = -1;
        }
    }

    return 0;
}

int hamCycle(Graph* g) {
    int numVertices = g->numVertices;
    int* path = (int*)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++)
        path[i] = -1;

    path[0] = 0;

    if (isHamiltonianCycle(g->adjMatrix, numVertices, path, 1) == 0) {
        printf("\nNo Hamiltonian path\n");
        free(path);
        return 0;
    }

    for (int i = 0; i < numVertices; i++)
        printf("%d ", path[i]);

    printf(" %d ", path[0]);
    printf("\n");

    free(path);
    return 1;
}

int main() {
    // Graph *graph = init_graph(4);
    // addEdge(graph, 0, 1);
    // addEdgeDirectional(graph, 1, 3);
    // addEdgeDirectional(graph, 2, 3);
    // addEdgeDirectional(graph, 1, 2);
    // addEdgeDirectional(graph, 0, 2);
    // addEdgeDirectional(graph, 0, 0);

    // printGraph(graph);
    // printf("\n");
    // printf("%d\n", isThereUniversalSink(graph));

    // Graph* g = init_graph(4);
    // addEdge(g, 1, 2);
    // addEdgeDirectional(g, 1, 0);
    // addEdgeDirectional(g, 2, 0);
    // addEdgeDirectional(g, 3, 0);
    // addEdge(g, 2, 3);
    // printf("%d\n", isThereUniversalSink(g));

    Graph* g3 = init_graph(5);
    addEdge(g3, 0, 1);
    addEdge(g3, 0, 2);
    addEdge(g3, 0, 3);
    addEdge(g3, 3, 2);
    addEdge(g3, 2, 1);
    addEdge(g3, 1, 4);
    addEdge(g3, 4, 2);
    hamCycle(g3);

    return 0;
}