#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int src; 
    int dest; 
    int weight;
} Edge;

typedef struct Subset {
    int parent;
} Subset;

int Find(Subset* subsets, int i) {
    if(subsets[i].parent == i) {
        return i;
    }

    return Find(subsets, subsets[i].parent);
}

void Union(Subset *subsets, int src, int dest) {
    subsets[src].parent = dest;
}

int compare(const void * a, const void * b) {
    Edge *e1 = (Edge*)a;
    Edge *e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

void Kruskal(Edge *edges, int V, int E) { //cqloto e O()
    qsort(edges, E, sizeof(Edge), compare); //O(ElogE)

    Edge* result = (Edge*)malloc((V - 1) * sizeof(Edge));
    int e = 0;
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));

    for(int i = 0; i < V; i++) { //V
        subsets[i] = (Subset){i};
    }

    for(int i = 0; i < E; i++) { // E * logV
        int root1 = Find(subsets, edges[i].src);
        int root2 = Find(subsets, edges[i].dest);

        if(root1 == root2) {
            continue;
        }

        result[e++] = edges[i];
        Union(subsets, root1, root2);
        
        if(e == V - 1)
            break;
    }

    for(int i = 0; i < E; i++) {
        printf("%d %d %d\n", edges[i].src, edges[i].dest, edges[i].weight);
    }
}

int main() {

    int V = 5;
    int E = 10;

    Edge *edges = (Edge*)malloc(V * sizeof(Edge));

    for(int i = 0; i < E; i++) {
        edges[i].src = i;
        edges[i].dest = i + 1;
        edges[i].weight = i + 2;
    }

    Kruskal(edges, V, E);

    return 0;
}