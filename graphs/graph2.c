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

void NodesWithDistanceN(Graph* G, int distance, int startNode) {
    DList *queue = init_dlist();
    insertBegin(queue, startNode);

    int* visited = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    int* parent = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    int* dist = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    visited[startNode] = 1;

    while(queue->head && dist[startNode] < distance) {
        int node = pop(queue);
        Node *current = G->adjList[node];
        while (current != NULL) {
            if (!visited[current->val]) {
                visited[current->val] = 1;
                insertBegin(queue, current->val);
                parent[current->val] = node;
                dist[current->val] = dist[node] + 1;
                
                if(dist[current->val] == distance)
                    printf("%d ", current->val);
            }
            current = current->next;
        }
    }

}

int hasCycle_R(Graph* G, int start, int* visited, DList* recursionStack) {
    Node *current = G->adjList[start];

    while (current) {
        if (!visited[current->val]) {
            visited[current->val] = 1;
            hasCycle_R(G, current->val, visited, recursionStack);
        } else {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

int hasCycle(Graph* G) {
    int* visited = (int*)calloc(G->numVertices, G->numVertices * sizeof(int));
    visited[0] = 1;
    DList* recursionStack = init_dlist();
    insertBegin(recursionStack, 0);
    int res = hasCycle_R(G, 0, visited, recursionStack);
    free(visited);

    return res;
}

int isThereUniversalSink(Graph* g) {
    Node *current = NULL;
    int flag = 0;
    int index = -1;

    for(int i = 0; i < g->numVertices; i++) {
        current = g->adjList[i];

        if(current == NULL) {
            index = i;
            break;
        }
    }

    if(index == -1)
        return 0;
    
    for(int i = 0; i < g->numVertices; i++) {
        if(i == index)
            continue;
        
        Node* test = g->adjList[i];
        while(test->next != NULL) {
            if(test->val == index) {
                flag = 1;
                break;
            }
            test = test->next;
        }

            if(flag == 0)
                return 0;
    }

    return 1;
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

    NodesWithDistanceN(graph, 2, graph->adjList[0]->val);
    printf("\n");
    printf("%d\n", hasCycle(graph));
    printf("%d\n", isThereUniversalSink(graph));

    Graph* g = init_graph(4);
    addEdge(g, 1, 2);
    addEdgeDirectional(g, 1, 0);
    addEdgeDirectional(g, 2, 0);
    addEdgeDirectional(g, 3, 0);
    addEdge(g, 2, 3);
    //printGraph(g);
    printf("test");
    printf("\nIS SINK %d\n", isThereUniversalSink(g));

    return 0;
}