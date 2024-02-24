/*stepen na vruh - kolko rebra vlizat v nego*/
#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

typedef struct Node {
    int val;
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

void addEdgeDirectional(Graph *graph, int from, int to)
{
    if (from < 0 || from >= graph->numVertices || to < 0 || to >= graph->numVertices) {
        printf("Invalid from or to\n");
        return;
    }

    Node *newNode = init_node(to);

    newNode->next = graph->adjList[from];
    graph->adjList[from] = newNode;
}

void addEdge(Graph *graph, int from, int to) {
    addEdgeDirectional(graph, from, to);
    addEdgeDirectional(graph, to, from);
}

void printGraph(Graph *graph)
{
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

void BFS(Graph* G) {
    DList *queue = init_dlist();
    insertBegin(queue, 0);

    int* visited = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    visited[0] = 1;

    while(queue->head) {
        int current = pop(queue);
        printf("%d ", current);

        Node* currentNode = G->adjList[current];
        while(currentNode) {
            if(!visited[currentNode->val]) {
                insertBegin(queue, currentNode->val);
                visited[currentNode->val] = 1;
            }

            currentNode = currentNode->next;
        }
    }
}

void BF2S(Graph* G) {
    DList *queue = init_dlist();
    insertBegin(queue, 0);

    int* visited = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    int* parent = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    int* dist = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    visited[0] = 1;

    while(queue->head) {
        int current = pop(queue);
        printf("%d ", current);

        Node* currentNode = G->adjList[current];
        while(currentNode) {
            if(!visited[currentNode->val]) {
                insertBegin(queue, currentNode->val);
                parent[currentNode->val] = current;
                dist[currentNode->val] = dist[current] + 1;
                visited[currentNode->val] = 1;
            }

            currentNode = currentNode->next;
        }
    }

    for(int i = 0; i < G->numVertices; i++)
        printf("\nParent of %d: %d at dist %d", i, parent[i], dist[i]);

}

int main() {
    Graph *graph = init_graph(6);
    addEdge(graph, 0, 1);
    addEdgeDirectional(graph, 1, 3);
    addEdgeDirectional(graph, 2, 3);
    addEdgeDirectional(graph, 1, 2);
    addEdgeDirectional(graph, 0, 2);
    addEdgeDirectional(graph, 0, 0);
    addEdge(graph, 3, 4);
    addEdgeDirectional(graph, 2, 4);
    addEdgeDirectional(graph, 4, 0);
    addEdgeDirectional(graph, 5, 4);
    addEdgeDirectional(graph, 5, 1);
    addEdgeDirectional(graph, 3, 5);
    addEdgeDirectional(graph, 3, 0);

    // printGraph(graph);
    // printf("\n");
    // BFS(graph);
    // printf("\n");
    BF2S(graph);

    return 0;
}