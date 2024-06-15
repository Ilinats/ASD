#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PQ_NODES 10000

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

int allKeysCollected(int keys_collected[], int totalKeys) {
    for (int i = 0; i < totalKeys; i++) {
        if (!keys_collected[i]) 
            return 0;
    }
    return 1;
}

int shortestPathAllKeys(char **grid, int m, int n) {
    PQueue *pq = init_pq();
    int startRow = 0, startCol = 0;
    int keyCount = 0;
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '@') {
                startRow = i;
                startCol = j;
            } else if (grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                keyCount = keyCount > (grid[i][j] - 'a' + 1) ? keyCount : (grid[i][j] - 'a' + 1);
            }
        }
    }

    State startState = {startRow, startCol, 0, {0}};
    pqInsert(pq, startState, 0);
    char visited[m][n][64];
    memset(visited, 0, sizeof(visited));
    visited[startRow][startCol][0] = 1;

    while (pq->size > 0) {
        PQNode currentNode = pqDeleteMin(pq);
        State s = currentNode.state;
        
        if (allKeysCollected(s.keys_collected, keyCount)) {
            free(pq);
            return s.steps;
        }
        
        int directions[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        for (int i = 0; i < 4; ++i) {
            int nr = s.r + directions[i][0], nc = s.c + directions[i][1];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != '#') {
                State newState = s;
                newState.r = nr;
                newState.c = nc;
                newState.steps++;
                char cell = grid[nr][nc];
                if (cell >= 'a' && cell <= 'f') {
                    newState.keys_collected[cell - 'a'] = 1;
                } else if (cell >= 'A' && cell <= 'F' && !s.keys_collected[cell - 'A']) {
                    continue; // Lock is there, and we don't have the key
                }
                if (!visited[nr][nc][newState.keys_collected[0] | newState.keys_collected[1] << 1 | newState.keys_collected[2] << 2 | newState.keys_collected[3] << 3 | newState.keys_collected[4] << 4 | newState.keys_collected[5] << 5]) {
                    visited[nr][nc][newState.keys_collected[0] | newState.keys_collected[1] << 1 | newState.keys_collected[2] << 2 | newState.keys_collected[3] << 3 | newState.keys_collected[4] << 4 | newState.keys_collected[5] << 5] = 1;
                    pqInsert(pq, newState, s.steps + 1);
                }
            }
        }
    }
    
    free(pq);
    return -1;
}

int main() {
    char *grid[] = {"@.a..", "###.#", "b.A.B"};
    int gridSize = 3;
    int gridWidth = strlen(grid[0]);

    printf("%d\n", shortestPathAllKeys(grid, gridSize, gridWidth));
    return 0;
}
