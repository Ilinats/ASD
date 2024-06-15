#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dlist.c" //TODO: change to .h
#include "pqueue.c" //TODO: change to .h
#define SIZE 8

//TODO: izmesti gi v obdhta funkciq trite i promeni samo za distance-a

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
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
};


void BFS(int startRow, int startCol, int endRow, int endCol) {
    DList *queue = init_dlist();
    insertBegin(queue, startRow * SIZE + startCol);
    
    int visited[SIZE][SIZE] = {{0}};
    int parents[SIZE][SIZE] = {{-1}};
    int dist[SIZE][SIZE] = {{0}};
    char new[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            new[i][j] = graph[i][j];
    }
    
    visited[startRow][startCol] = 1;
    
    while (queue->head != NULL) {
        int current = pop(queue);

        if(graph[current/SIZE][current%SIZE] != 'S' && graph[current/SIZE][current%SIZE] != 'E') {
            new[current/SIZE][current%SIZE] = '.';
            pathVisualiser(new);
        }
        
        int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int k = 0; k < 4; k++) {
            int newRow = current / SIZE + moves[k][0];
            int newCol = current % SIZE + moves[k][1];

            if (newRow == endRow && newCol == endCol) {
                parents[newRow][newCol] = current;
                dist[newRow][newCol] = dist[current/SIZE][current%SIZE] + 1;
                visited[newRow][newCol] = 1;
                while (parents[newRow][newCol] != -1) {
                    new[newRow][newCol] = 'X';
                    pathVisualiser(new);
                    int tempRow = newRow, tempCol = newCol;
                    newRow = parents[tempRow][tempCol] / SIZE;
                    newCol = parents[tempRow][tempCol] % SIZE;
                }
                printf("\n");
                return;
            }

            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE &&
                graph[newRow][newCol] != '#' && !visited[newRow][newCol]) {
                insertBegin(queue, newRow * SIZE + newCol);
                parents[newRow][newCol] = current;
                dist[newRow][newCol] = dist[current/SIZE][current%SIZE] + 1;
                visited[newRow][newCol] = 1;
            }
        }
    }
}

float heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void AStar(int start, int end) { //use weight 2 
    int *visited = (int *)calloc(g->numVertices, sizeof(int));
    float *dist = (float *)calloc(g->numVertices, sizeof(float));
    PQueue *pq = init_pq();
    pqInsert(pq, start, 0);
    visited[start] = 1;
    dist[start] = 0;

    while (pq->size > 0)
    {
        PQNode *current = deleteMin(pq);
        int vertex = current->data;

        if (vertex == end)
            return;

        visited[vertex] = 1;
        
        Node *v_node = g->adjLists[vertex];
        while (v_node != NULL)
        {
            if (!visited[v_node->val])
            {
                dist[v_node->val] = dist[vertex] + v_node->weight;
                float g = dist[v_node->val];
                float h = heuristic(v_node->val / SIZE, v_node->val % SIZE, end / SIZE, end % SIZE);
                float f = g + h;

                pqInsert(pq, v_node->val, f);
                visited[v_node->val] = 1;
            }

            v_node = v_node->next;
        }
        // while (v_node != NULL)
        // {
        //     if (!visited[v_node->val])
        //     {
        //         dist[v_node->val] = dist[vertex] + v_node->weight;
        //         float g = dist[v_node->val]; // Djikstra
        //         float h = v_node->weight;    // Best first
        //         float f = h;                 // A*

        //         pqInsert(pq, v_node, f);
        //         visited[v_node->val] = 1;
        //     }

        //     v_node = v_node->next;
        // }
    }

    printf("No path found.\n");
    return;
}

void printShortestPath(int startRow, int startCol, int endRow, int endCol, int parents[][SIZE]) {
    printf("Shortest Path:\n");
    int currentRow = endRow;
    int currentCol = endCol;
    char path[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            path[i][j] = graph[i][j];
        }
    }
    while (currentRow != startRow || currentCol != startCol) {
        path[currentRow][currentCol] = 'X';
        pathVisualiser(path);
        int tempRow = currentRow, tempCol = currentCol;
        currentRow = parents[tempRow][tempCol] / SIZE;
        currentCol = parents[tempRow][tempCol] % SIZE;
    }
    path[startRow][startCol] = 'S';
    pathVisualiser(path);
}

void Dijkstra(int startRow, int startCol, int endRow, int endCol) {
    int distance[SIZE][SIZE];
    int visited[SIZE][SIZE] = {{0}};
    int parents[SIZE][SIZE];
    char new[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            distance[i][j] = INT_MAX;
            new[i][j] = graph[i][j];
        }
    }

    distance[startRow][startCol] = 0;

    for (int count = 0; count < SIZE * SIZE; count++) {
        int minDistance = INT_MAX;
        int minRow = -1;
        int minCol = -1;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (!visited[i][j] && weights[i][j] != -1 && distance[i][j] < minDistance) {
                    minDistance = distance[i][j];
                    minRow = i;
                    minCol = j;
                }
            }
        }

        new[minRow][minCol] = '.';
        pathVisualiser(new);
        //printf("Min: %d %d\n", minRow, minCol);

        if (minRow == endRow && minCol == endCol) {
            printShortestPath(startRow, startCol, endRow, endCol, parents);
            return;
        }

        visited[minRow][minCol] = 1;

        int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int k = 0; k < 4; k++) {
            int newRow = minRow + moves[k][0];
            int newCol = minCol + moves[k][1];

            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && !visited[newRow][newCol] && weights[newRow][newCol] != -1) {
                int newDistance = distance[minRow][minCol] + weights[newRow][newCol];
                if (newDistance < distance[newRow][newCol]) {
                    distance[newRow][newCol] = newDistance;
                    parents[newRow][newCol] = minRow * SIZE + minCol;
                }
            }
        }
    }

    printf("No path found.\n");
}

int main() {
    int startRow, startCol, endRow, endCol;

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(graph[i][j] == 'S') {
                startRow = i;
                startCol = j;
            }
            if(graph[i][j] == 'E') {
                endRow = i;
                endCol = j;
            }
        }
    }

    while(1) {
        printf("Choose the algorithm you want to use: \n");
        printf("1. BFS\n");
        printf("2. A*\n");
        printf("3. Dijkstra\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                BFS(startRow, startCol, endRow, endCol);
                break;

            case 2:
                AStar();
                break;

            case 3:
                Dijkstra(startRow, startCol, endRow, endCol);
                break;

            case 4:
                exit(0);
                break;
        
            default:
                break;
        }

    }

    return 0;
}