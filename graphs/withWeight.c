#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

typedef struct Node {
    int val;
    int weight;
    struct Node *next;
} Node;

typedef struct Graph {
    int numVertices;
    Node **adjList;
} Graph;

Node *init_node(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;

    return node;
}

Graph *init_graph(int numVertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjList = (Node **)calloc(numVertices, sizeof(Node *));

    return graph;
}

void addEdgeDirectional(Graph *graph, int from, int to, int weight) {
    if (from < 0 || from >= graph->numVertices || to < 0 || to >= graph->numVertices) {
        printf("Invalid from or to\n");
        return;
    }

    Node *newNode = init_node(to);

    newNode->next = graph->adjList[from];
    graph->adjList[from] = newNode;
    newNode->weight = weight;
}

void addEdge(Graph *graph, int from, int to, int weight1, int weight2) {
    addEdgeDirectional(graph, from, to, weight1);
    addEdgeDirectional(graph, to, from, weight2);
}

void printGraph(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node *current = graph->adjList[i];
        printf("Neighbours of %d:\n", i);
        while (current != NULL) {
            printf("%d ", current->val);
            current = current->next;
        }
        printf("\n");
    }
}

void printWithWeights(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node *current = graph->adjList[i];
        printf("Neighbours of %d:\n", i);
        while (current != NULL) {
            printf("%d ", current->val);
            printf("Weight: %d\n", current->weight);
            current = current->next;
        }
        printf("\n");
    }
}

void Dijkstra(Graph* g) {
    int* distance = (int*)malloc(g->numVertices * sizeof(int));
    int* visited = (int*)malloc(g->numVertices * sizeof(int));

    for (int i = 0; i < g->numVertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[0] = 0;

    for (int count = 0; count < g->numVertices - 1; count++) {
        int min = INT_MAX;
        int minIndex;

        for (int v = 0; v < g->numVertices; v++) {
            if (visited[v] == 0 && distance[v] <= min) {
                min = distance[v];
                minIndex = v;
            }
        }

        printf("minIndex: %d\n", minIndex);

        visited[minIndex] = 1;

        Node* current = g->adjList[minIndex];
        while (current != NULL) {
            int alt = distance[minIndex] + current->weight;
            if (alt < distance[current->val]) {
                distance[current->val] = alt;
            }
            current = current->next;
        }
    }

    for (int i = 0; i < g->numVertices; i++)
        printf("%d ", distance[i]);

    printf("\n");

    free(distance);
    free(visited);
};

void Prim(Graph* g) {
    int* distance = (int*)malloc(g->numVertices * sizeof(int));
    int* visited = (int*)malloc(g->numVertices * sizeof(int));

    for (int i = 0; i < g->numVertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[0] = 0;

    for (int count = 0; count < g->numVertices - 1; count++) {
        int min = INT_MAX;
        int minIndex;

        for (int v = 0; v < g->numVertices; v++) {
            if (visited[v] == 0 && distance[v] <= min) {
                min = distance[v];
                minIndex = v;
            }
        }

        printf("minIndex: %d\n", minIndex);

        visited[minIndex] = 1;

        Node* current = g->adjList[minIndex];
        while (current != NULL) {
            int alt = current->weight;
            if (alt < distance[current->val]) {
                distance[current->val] = alt;
            }
            current = current->next;
        }
    }

    for (int i = 0; i < g->numVertices; i++) {
        printf("%d ", distance[i]);
    }
    printf("\n");

    free(distance);
    free(visited);
}

int main() {
    Graph *graph = init_graph(5);
    // addEdgeDirectional(graph, 0, 1, 10);
    // addEdgeDirectional(graph, 0, 2, 5);
    // addEdge(graph, 1, 2, 2, 3);
    // addEdgeDirectional(graph, 2, 3, 9);
    // addEdgeDirectional(graph, 1, 3, 1);
    // addEdgeDirectional(graph, 2, 4, 2);
    // addEdge(graph, 3, 4, 4, 6);
    // addEdgeDirectional(graph, 4, 0, 7);

    addEdgeDirectional(graph, 0, 1, 2);
    addEdgeDirectional(graph, 0, 2, 1);
    addEdgeDirectional(graph, 2, 3, 1);
    addEdgeDirectional(graph, 3, 4, 1);
    addEdgeDirectional(graph, 4, 1, 1);

    Dijkstra(graph);
    //printWithWeights(graph);
    Prim(graph);

    return 0;
}