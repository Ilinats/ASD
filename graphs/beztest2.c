#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PQ_NODES 10000
/*You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle). You can move up, down, left, or right from and to an empty cell in one step.
Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1) given that you can eliminate at most k obstacles. 
If it is not possible to find such walk return -1.*/

typedef struct {
    int r, c;
    int steps;
    int keys_collected[6];
} State;

typedef struct {
    float key;
    State state;
} PQNode;

typedef struct {
    PQNode arr[MAX_PQ_NODES];
    int size;
} PQueue;

PQueue *init_pq() {
    PQueue *pq = (PQueue *)malloc(sizeof(PQueue));
    pq->size = 0;
    return pq;
}

void pqInsert(PQueue *pq, State state, float priority) {
    if (pq->size >= MAX_PQ_NODES) {
        return; 
    }
    int i = pq->size++;
    pq->arr[i].key = priority;
    pq->arr[i].state = state;

    while (i != 0) {
        int parent = (i - 1) / 2;
        if (pq->arr[parent].key <= pq->arr[i].key) break;
        PQNode tmp = pq->arr[i];
        pq->arr[i] = pq->arr[parent];
        pq->arr[parent] = tmp;
        i = parent;
    }
}

PQNode pqDeleteMin(PQueue *pq) {
    PQNode minNode = pq->arr[0];
    pq->arr[0] = pq->arr[--pq->size];
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = left + 1;
        int smallest = i;
        if (left < pq->size && pq->arr[left].key < pq->arr[smallest].key) {
            smallest = left;
        }
        if (right < pq->size && pq->arr[right].key < pq->arr[smallest].key) {
            smallest = right;
        }
        if (smallest == i) break;
        PQNode tmp = pq->arr[i];
        pq->arr[i] = pq->arr[smallest];
        pq->arr[smallest] = tmp;
        i = smallest;
    }
    return minNode;
}

int shortestPath(int** grid, int gridSize, int* gridColSize, int k) {
    
}