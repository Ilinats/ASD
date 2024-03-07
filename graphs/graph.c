/*stepen na vruh - kolko rebra vlizat v nego
BFS връща по-оптимален път, DFS е на random*/
#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

typedef struct Node {
    int val;
    int color;
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
    node->color = -1;

    return node;
}

Graph *init_graph(int numVertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjList = (Node **)calloc(numVertices, sizeof(Node *));

    return graph;
}

void addEdgeDirectional(Graph *graph, int from, int to) {
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

void removeEdge(Graph *graph, int from, int to) {
    Node *current = graph->adjList[from];
    Node *prev = NULL;

    while (current != NULL) {
        if (current->val == to) {
            if (prev == NULL) {
                graph->adjList[from] = current->next;
                free(current);
                return;
            }

            prev->next = current->next;
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
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

void DFS(Graph* G) {
    DList *stack = init_dlist();
    insertBegin(stack, 0);

    int* visited = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    int* parent = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    int* dist = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    visited[0] = 1;

    while(stack->head) {
        int current = popFront(stack);
        printf("%d ", current);

        Node* currentNode = G->adjList[current];
        while(currentNode) {
            if(!visited[currentNode->val]) {
                insertBegin(stack, currentNode->val);
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

void DFS2_R(Graph* G, int start, int* visited) {
    Node *currentNode = G->adjList[start];
    printf("%d ", start);

    while(currentNode) {
        if(!visited[currentNode->val]) {
            visited[currentNode->val] = 1;
            DFS2_R(G, currentNode->val, visited);
        }

        currentNode = currentNode->next;
    }
}

void DFS2(Graph* G) {
    int* visited = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    visited[0] = 1;
    DFS2_R(G, 0, visited);
    free(visited);
}

void Teams_R(Graph* G, int start, int* visited, int team) {
    Node *currentNode = G->adjList[start];
    printf("%d ", start);

    while(currentNode) {
        if(!visited[currentNode->val]) {
            visited[currentNode->val] = 1;
            if(currentNode->color == -1 || currentNode->color == !team)
                Teams_R(G, currentNode->val, visited, !team);
            else {
                printf("Not bipartite\n");
                return;
            }
        }

        currentNode = currentNode->next;
    }
}

void Teams(Graph* G, int team) {
    int* visited = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    visited[0] = 1;
    Teams_R(G, 0, visited, team);
    free(visited);
}

void isTherePath(Graph* G, int from, int to) {
    DList *queue = init_dlist();
    insertBegin(queue, from);

    int* visited = (int*)calloc(G->numVertices, sizeof(int));
    int* distance = (int*)calloc(G->numVertices, sizeof(int));
    int* parent = (int*)calloc(G->numVertices, sizeof(int));
    visited[from] = 1;

    while(queue->head) {
        int current = pop(queue);

        if(current == to) {
            printf("Distance: %d\n", distance[current]);
            printf("Path: ");
            int temp = current;

            while (temp != from) {
                printf("%d ", temp);
                temp = parent[temp];
            }

            printf("%d\n", from);
            return;
        }

        Node* currentNode = G->adjList[current];

        while(currentNode) {
            if(!visited[currentNode->val]) {
                insertBegin(queue, currentNode->val);
                visited[currentNode->val] = 1;
                distance[currentNode->val] = distance[current] + 1;
                parent[currentNode->val] = current;
            }

            currentNode = currentNode->next;
        }
    }

    printf("No path found\n");
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
    //BF2S(graph);
    isTherePath(graph, 0, 5);

    return 0;
}