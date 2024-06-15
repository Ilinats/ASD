#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_SIZE 8
/*You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.

You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.

Example 1:

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
note: x is undefined => -1.0*/

typedef struct EntryNode
{
    char *key;
    void *val;
    struct EntryNode *next;
} EntryNode;

typedef struct HashMap
{
    EntryNode **array;
} HashMap;

typedef struct VertexNode
{
    char *val;
    double weight;
    struct VertexNode *next;
} VertexNode;

typedef struct Graph
{
    HashMap *adjList;
} Graph;

EntryNode *init_entry(char *key, void *val)
{
    EntryNode *entry = (EntryNode *)malloc(sizeof(EntryNode));
    entry->key = key;
    entry->val = val;
    entry->next = NULL;

    return entry;
}

HashMap *init_hash_map()
{
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->array = (EntryNode **)calloc(HASH_SIZE, sizeof(EntryNode *));

    return map;
}

int hash(char *key)
{
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        sum += key[i];
    }

    return sum % HASH_SIZE;
}

void set(HashMap *hash_map, char *key, void *val)
{
    int index = hash(key);
    EntryNode *entry = init_entry(key, val);

    if (hash_map->array[index] == NULL)
    {
        hash_map->array[index] = entry;
    }
    else
    {
        EntryNode *it = hash_map->array[index];

        while (it != NULL)
        {
            if (strcmp(it->key, key) == 0)
            {
                it->val = val;
                // free entry;
                return;
            }

            if (it->next == NULL)
            {
                break;
            }
            it = it->next;
        }

        it->next = entry;
    }
}

void *get(HashMap *hash_map, char *key)
{
    int index = hash(key);

    if (hash_map->array[index] == NULL)
    {
        return NULL;
    }

    EntryNode *it = hash_map->array[index];

    while (it != NULL)
    {
        if (strcmp(it->key, key) == 0)
        {
            return it->val;
        }
        it = it->next;
    }

    return NULL;
}

VertexNode *init_node(char *val, double weight)
{
    VertexNode *node = (VertexNode *)malloc(sizeof(VertexNode));
    node->val = strdup(val);
    node->next = NULL;
    node->weight = weight;

    return node;
}

Graph *init_graph()
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->adjList = init_hash_map();

    return graph;
}

void addEdgeDirectional(Graph *graph, char *from, char *to, double weight)
{
    VertexNode *newNode = init_node(to, weight);

    newNode->next = get(graph->adjList, from);
    set(graph->adjList, from, newNode);
}

void addEdge(Graph *graph, char *from, char *to, double weight)
{
    addEdgeDirectional(graph, from, to, weight);
    addEdgeDirectional(graph, to, from, weight);
}

void printGraph(Graph *graph)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        EntryNode *current = graph->adjList->array[i];
        if (current == NULL)
        {
            continue;
        }

        while (current != NULL)
        {
            VertexNode *currentNode = (VertexNode *)current->val;
            printf("Neighbours of %s:\n", current->key);
            while (currentNode != NULL)
            {
                printf("%s(%f) ", currentNode->val, currentNode->weight);
                currentNode = currentNode->next;
            }
            current = current->next;
            printf("\n");
        }
    }
}

int dfs(Graph *graph, char *current, char *target, double *result, HashMap *visited) {
    if (strcmp(current, target) == 0)
        return 1;
    
    set(visited, current, (void*)1); 
    VertexNode *neighbors = (VertexNode *)get(graph->adjList, current);

    while (neighbors != NULL) {
        if (get(visited, neighbors->val) == NULL) {
            *result *= neighbors->weight;

            if (dfs(graph, neighbors->val, target, result, visited))
                return 1;

            *result /= neighbors->weight;
        }
        neighbors = neighbors->next;
    }

    return 0;
}

double* calcEquation(char* equations[][2], int equationsSize, int* equationsColSize, 
double* values, int valuesSize, char* queries[][2], int queriesSize, int* queriesColSize, int* returnSize) {
    //stroim kato graph a -> b -> c; i kato ttegla slagame valuetata i umnojavame po putq
    //                    2     3
    //                  a <- b <- c
    //                    1/2  1/3

    // trqbwa da izpozlvame graph s adj list, kojto e hashmap 

    Graph *graph = init_graph();

    for (int i = 0; i < equationsSize; i++) {
        addEdgeDirectional(graph, equations[i][0], equations[i][1], values[i]);
        addEdgeDirectional(graph, equations[i][1], equations[i][0], 1 / values[i]);
    }

    double *result = (double *)malloc(queriesSize * sizeof(double));
    for (int i = 0; i < queriesSize; i++) {
        char *from = queries[i][0];
        char *to = queries[i][1];

        if (get(graph->adjList, from) == NULL || get(graph->adjList, to) == NULL) {
            result[i] = -1.0;
            continue;
        }

        if (strcmp(from, to) == 0) {
            result[i] = 1.0;
            continue;
        }

        double res = 1.0;
        HashMap *visited = init_hash_map();

        if (dfs(graph, from, to, &res, visited))
            result[i] = res;
        else
            result[i] = -1.0;
    }

    *returnSize = queriesSize;
    return result;
}

int main()
{
    char *equations[2][2] = {{"a", "b"}, {"b", "c"}};
    double values[2] = {2.0, 3.0};
    char *queries[5][2] = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    int returnSize;
    double *result = calcEquation(equations, 2, NULL, values, 2, queries, 5, NULL, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%f ", result[i]);
    }
    return 0;
}