#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dlist.c" // Changed from .c to .h
#include "pqueue.c" // Changed from .c to .h
#define SIZE 8

char graph[SIZE][SIZE] = {{'#', '#', '#', '#', '#', '#', '#', '#'},
                          {'#', 'S', ' ', ' ', ' ', ' ', ' ', '#'},
                          {'#', '#', '#', ' ', ' ', ' ', ' ', '#'}, 
                          {'#', ' ', ' ', ' ', ' ', ' ', '#', '#'}, 
                          {'#', ' ', ' ', '#', '#', 'E', ' ', '#'}, 
                          {'#', ' ', ' ', ' ', ' ', '#', ' ', '#'}, 
                          {'#', ' ', '#', ' ', ' ', ' ', ' ', '#'}, 
                          {'#', '#', '#', '#', '#', '#', '#', '#'}};

int weights[SIZE][SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1},
                           {-1, 0, 5, 3, 8, 1, 9, -1},
                           {-1, -1, -1, 1, 1, 1, 3, -1}, 
                           {-1, 10, 2, 3, 2, 1100, -1, -1}, 
                           {-1, 5, 5, -1, -1, 0, 2, -1}, 
                           {-1, 1, 1, 1, 13, -1, 4, -1}, 
                           {-1, 3, -1, 10, 9, 8, 5, -1}, 
                           {-1, -1, -1, -1, -1, -1, -1, -1}};

int weights2[SIZE][SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1},
                            {-1, 0, 10, 10, 10, 10, 10, -1},
                            {-1, -1, -1, 10, 10, 10, 10, -1}, 
                            {-1, 10, 10, 10, 10, 10, -1, -1}, 
                            {-1, 10, 10, -1, -1, 0, 10, -1}, 
                            {-1, 10, 10, 10, 10, -1, 10, -1}, 
                            {-1, 10, -1, 10, 10, 10, 10, -1}, 
                            {-1, -1, -1, -1, -1, -1, -1, -1}};


void pathVisualiser(char (*arr)[SIZE]) {
    Sleep(300);
    system("cls");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
}

void initVariables(int dist[][SIZE], int parents[][SIZE], int visited[][SIZE], char newGraph[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            dist[i][j] = INT_MAX;
            parents[i][j] = -1;
            visited[i][j] = 0;
            newGraph[i][j] = graph[i][j];
        }
    }
}

float heuristic(int x1, int y1, int x2, int y2) {
    return (abs(x1 - x2) + abs(y1 - y2)) * 1.01;
}

typedef struct {
    int row;
    int col;
} Node;

typedef int (*NextNodeFunc)(Node *current, Node *next, int endRow, int endCol, int dist[][SIZE], int parents[][SIZE], int visited[][SIZE], PQueue *pq);

int BFSNextNode(Node *current, Node *next, int endRow, int endCol, int dist[][SIZE], int parents[][SIZE], int visited[][SIZE], PQueue *pq) {
    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int k = 0; k < 4; k++) {
        int newRow = current->row + moves[k][0];
        int newCol = current->col + moves[k][1];

        if (newRow == endRow && newCol == endCol) {
            parents[newRow][newCol] = current->row * SIZE + current->col;
            dist[newRow][newCol] = dist[current->row][current->col] + 1;
            visited[newRow][newCol] = 1;
            next->row = newRow;
            next->col = newCol;
            return 1;
        }

        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE &&
            graph[newRow][newCol] != '#' && !visited[newRow][newCol]) {
            Node newNode = {newRow, newCol};
            pqInsert(pq, (void *)(newRow * SIZE + newCol), 0);
            parents[newRow][newCol] = current->row * SIZE + current->col;
            dist[newRow][newCol] = dist[current->row][current->col] + 1;
            visited[newRow][newCol] = 1;
        }
    }
    return 0;
}

int AStarNextNode(Node *current, Node *next, int endRow, int endCol, int dist[][SIZE], int parents[][SIZE], int visited[][SIZE], PQueue *pq) {
    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    float bestCost = INT_MAX;
    int bestRow = -1, bestCol = -1;

    for (int k = 0; k < 4; k++) {
        int newRow = current->row + moves[k][0];
        int newCol = current->col + moves[k][1];

        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && graph[newRow][newCol] != '#' && !visited[newRow][newCol]) {
            float newDist = dist[current->row][current->col] + weights2[newRow][newCol];
            float newCost = newDist + heuristic(newRow, newCol, endRow, endCol);
            if (newCost < bestCost) {
                bestCost = newCost;
                bestRow = newRow;
                bestCol = newCol;
            }
        }
    }

    if (bestRow != -1 && bestCol != -1) {
        dist[bestRow][bestCol] = dist[current->row][current->col] + weights2[bestRow][bestCol];
        parents[bestRow][bestCol] = current->row * SIZE + current->col;
        pqInsert(pq, (void *)(bestRow * SIZE + bestCol), bestCost);
        next->row = bestRow;
        next->col = bestCol;
        return 0;
    }
    return 1;
}

int DijkstraNextNode(Node *current, Node *next, int endRow, int endCol, int dist[][SIZE], int parents[][SIZE], int visited[][SIZE], PQueue *pq) {
    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int k = 0; k < 4; k++) {
        int newRow = current->row + moves[k][0];
        int newCol = current->col + moves[k][1];

        if (newRow == endRow && newCol == endCol) {
            parents[newRow][newCol] = current->row * SIZE + current->col;
            dist[newRow][newCol] = dist[current->row][current->col] + weights[newRow][newCol];
            visited[newRow][newCol] = 1;
            next->row = newRow;
            next->col = newCol;
            return 1;
        }

        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && !visited[newRow][newCol] && weights[newRow][newCol] != -1) {
            int newDist = dist[current->row][current->col] + weights[newRow][newCol];
            if (newDist < dist[newRow][newCol]) {
                dist[newRow][newCol] = newDist;
                parents[newRow][newCol] = current->row * SIZE + current->col;
                pqInsert(pq, (void *)(newRow * SIZE + newCol), newDist);
            }
        }
    }
    return 0;
}

void findPath(int startRow, int startCol, int endRow, int endCol, NextNodeFunc nextNodeFunc) {
    int visited[SIZE][SIZE];
    int dist[SIZE][SIZE];
    int parents[SIZE][SIZE];
    char newGraph[SIZE][SIZE];
    initVariables(dist, parents, visited, newGraph);

    PQueue *pq = init_pq();
    pqInsert(pq, (void *)(startRow * SIZE + startCol), 0);
    dist[startRow][startCol] = 0;

    while (pq->size > 0) {
        PQNode *currentPQNode = deleteMin(pq);
        int current = (int)currentPQNode->data;
        int currentRow = current / SIZE;
        int currentCol = current % SIZE;
        free(currentPQNode);

        Node currentNode = {currentRow, currentCol};
        Node nextNode;

        if (graph[currentRow][currentCol] != 'S' && graph[currentRow][currentCol] != 'E') {
            newGraph[currentRow][currentCol] = '.';
            pathVisualiser(newGraph);
        }

        if (currentRow == endRow && currentCol == endCol) {
            while (parents[currentRow][currentCol] != -1) {
                newGraph[currentRow][currentCol] = 'X';
                pathVisualiser(newGraph);
                int temp = parents[currentRow][currentCol];
                currentRow = temp / SIZE;
                currentCol = temp % SIZE;
            }
            newGraph[startRow][startCol] = 'S';
            newGraph[endRow][endCol] = 'E';
            pathVisualiser(newGraph);
            return;
        }

        visited[currentRow][currentCol] = 1;
        if (nextNodeFunc(&currentNode, &nextNode, endRow, endCol, dist, parents, visited, pq)) {
            break;
        }
    }

    printf("No path found.\n");
}

void BFS(int startRow, int startCol, int endRow, int endCol) {
    findPath(startRow, startCol, endRow, endCol, BFSNextNode);
}

void AStar(int startRow, int startCol, int endRow, int endCol) {
    findPath(startRow, startCol, endRow, endCol, AStarNextNode);
}

void Dijkstra(int startRow, int startCol, int endRow, int endCol) {
    findPath(startRow, startCol, endRow, endCol, DijkstraNextNode);
}

int main() {
    // Test BFS
    printf("BFS:\n");
    BFS(1, 1, 4, 5);
    
    // Test A*
    printf("A*:\n");
    AStar(1, 1, 4, 5);
    
    // Test Dijkstra
    printf("Dijkstra:\n");
    Dijkstra(1, 1, 4, 5);
    
    return 0;
}
