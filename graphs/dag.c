/*Как бихме могли да намерим най-късия и най-дългия път в граф с тегла на ребрата в линейно време ако знаем, че е DAG?:
    Можем да намерим най-късия и най-дългия път за линейно време след като graph-ът е топологично сортиран и след това
    инициализираме всички разстояния kato bezkrajnost, освен на началния - to e 0. Обхождаме ги в ред на топологичното 
    сортиране, защото няма да се връщаме назад. За най-къс път: гледаме всички изходящи редра и 
    update-ваме стойностите dist[v] < dist[u] + weight(u, v)  ? dist[v] : dist[u] + weight(u, v))
    За най-дълъг: dist[v] > dist[u] + weight(u, v) ? dist[v] : dist[u] + weight(u, v))*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

void findOrder(char *words[], int n, char *alpha) {
    int graph[MAX_CHAR][MAX_CHAR] = {0};
    int indegree[MAX_CHAR] = {0};
    int chars[MAX_CHAR] = {0};
    int i, j;

    for (i = 0; i < n - 1; i++) {
        char *word1 = words[i];
        char *word2 = words[i + 1];
        for (j = 0; word1[j] && word2[j]; j++) {
            if (word1[j] != word2[j]) {
                int u = word1[j];
                int v = word2[j];
                if (graph[u][v] == 0) {
                    graph[u][v] = 1;
                    indegree[v]++;
                }
                break;
            }
        }
        for (j = 0; word1[j]; j++) chars[word1[j]] = 1;
        for (j = 0; word2[j]; j++) chars[word2[j]] = 1;
    }

    int queue[MAX_CHAR], front = 0, rear = 0;
    for (i = 0; i < MAX_CHAR; i++) {
        if (chars[i] && indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int idx = 0;
    while (front < rear) {
        int u = queue[front++];
        alpha[idx++] = (char)u;
        for (i = 0; i < MAX_CHAR; i++) {
            if (graph[u][i]) {
                if (--indegree[i] == 0) {
                    queue[rear++] = i;
                }
            }
        }
    }

    alpha[idx] = '\0';

    if (idx != rear)
        printf("Invalid input: cycle detected or incomplete.\n");
}

int main() {
    char *words[] = {"daa", "bra", "bum"};
    int n = sizeof(words) / sizeof(words[0]);
    char alpha[MAX_CHAR];

    findOrder(words, n, alpha);
    printf("Alphabet order: %s\n", alpha);

    return 0;
}
