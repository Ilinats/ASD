#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 100

typedef struct Flight {
    int dest;
    int price;
    struct Flight* next;
} Flight;

typedef struct city {
    char* name;
    Flight* flights;
} City;

typedef struct {
    City cities[MAX_CITIES];
    int numCities;
} Graph;

typedef struct route {
    int totalCost;
    int stops;
    int path[MAX_CITIES];
} Route;

Graph* init_graph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numCities = 0;
    return graph;
}

void addCity(Graph* graph, const char* name) {
    if (graph->numCities == MAX_CITIES) {
        printf("Max city limit reached.\n");
        return;
    }
    graph->cities[graph->numCities].name = strdup(name);
    graph->cities[graph->numCities].flights = NULL;
    graph->numCities++;
}

int findCity(Graph* graph, const char* name) {
    for (int i = 0; i < graph->numCities; i++) {
        if (strcmp(graph->cities[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
    
}

void addFlight(Graph* graph, const char* from, const char* to, int price) {
    int fromIndex = findCity(graph, from);
    int toIndex = findCity(graph, to);

    if (fromIndex == -1 || toIndex == -1) {
        printf("Invalid city names\n");
        return;
    }

    Flight* newFlight = (Flight*)malloc(sizeof(Flight));
    newFlight->dest = toIndex;
    newFlight->price = price;
    newFlight->next = graph->cities[fromIndex].flights;
    graph->cities[fromIndex].flights = newFlight;
}

int routeCompare(const void* a, const void* b) {
    const Route* routeA = (const Route*)a;
    const Route* routeB = (const Route*)b;
    if (routeA->totalCost != routeB->totalCost) {
        return routeA->totalCost - routeB->totalCost;
    }
    return routeA->stops - routeB->stops;
}

void findRoutes(Graph* graph, int current, int destination, int stops, int maxStops, int cost, int maxCost, int path[], int pathIndex, int* visited, Route* routes, int* numRoutes) {
    if (cost > maxCost || stops > maxStops) return;
    if (current == destination) {
        routes[*numRoutes].totalCost = cost;
        routes[*numRoutes].stops = stops;
        memcpy(routes[*numRoutes].path, path, pathIndex * sizeof(int));
        (*numRoutes)++;
        return;
    }

    visited[current] = 1;
    for (Flight* f = graph->cities[current].flights; f != NULL; f = f->next) {
        if (!visited[f->dest]) {
            path[pathIndex] = f->dest;
            findRoutes(graph, f->dest, destination, stops + 1, maxStops, cost + f->price, maxCost, path, pathIndex + 1, visited, routes, numRoutes);
        }
    }
    visited[current] = 0;
}

void printRoute(Graph* graph, int path[], int stops) {
    for (int i = 0; i <= stops; i++) {
        printf("%s -> ", graph->cities[path[i]].name);
    }
    printf("End\n");
}

int main() {
    Graph* graph = init_graph();

    addCity(graph, "Sofia");
    addCity(graph, "London");
    addCity(graph, "Paris");
    addCity(graph, "Berlin");
    addCity(graph, "Madrid");

    addFlight(graph, "Sofia", "London", 200);
    addFlight(graph, "Sofia", "Paris", 500);
    addFlight(graph, "London", "Berlin", 300);
    addFlight(graph, "Paris", "Berlin", 100);
    addFlight(graph, "Berlin", "Madrid", 400);
    addFlight(graph, "Madrid", "Sofia", 600);

    char startCity[50], endCity[50];
    int maxStops, maxPrice;

    printf("Enter start city: ");
    scanf("%s", startCity);
    printf("Enter end city: ");
    scanf("%s", endCity);
    printf("Enter max number of stops: ");
    scanf("%d", &maxStops);
    printf("Enter max price: ");
    scanf("%d", &maxPrice);

    int startIndex = findCity(graph, startCity);
    int endIndex = findCity(graph, endCity);

    if (startIndex == -1 || endIndex == -1) {
        printf("City not found.\n");
        return 1;
    }

    int path[MAX_CITIES], visited[MAX_CITIES] = {0}, numRoutes = 0;
    Route routes[100];
    path[0] = startIndex;
    findRoutes(graph, startIndex, endIndex, 0, maxStops, 0, maxPrice, path, 1, visited, routes, &numRoutes);

    if (numRoutes == 0) {
        printf("No routes found.\n");
    } else {
        qsort(routes, numRoutes, sizeof(Route), routeCompare);
        for (int i = 0; i < numRoutes; i++) {
            printf("Cost: $%d, Stops: %d, Path: ", routes[i].totalCost, routes[i].stops);
            printRoute(graph, routes[i].path, routes[i].stops);
        }
    }

    return 0;
}
