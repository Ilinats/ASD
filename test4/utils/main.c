#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Имате да взимате N предмета, отбелязани от 0 до n-1. Като вход на
    програмата получавате масив от условия. Условията са двойка
    предмети [a, b] и тяхното значение е - “предмет a , трябва да се
    вземе преди предмет b”. Да се изведе дали е възможно предметите
    да се вземат с дадените условия.
    Пример:
    [[0,1], [1, 2], [3, 2]] - възможно е. 0, 1, 3, 2 е вариант.
    [[3,4], [4,5], [0, 3], [2, 5], [5, 0]] - не е възможно.
    Няма нужда да валидирате по някакъв начин входа. Гарантирано е
    че всяко условие е с коректни числа (от 0 до n-1) и съдържа точно
    два елемента.
    Обяснете в коментар (дори и да сте успели да направите кода)
    каква е идеята на решението ви, как работи и каква е неговата
    сложност по време.
    
    Коментар обяснение:
    Идеята на решението е да се използва алгоритъм за топологично сортиране, който е базиран на DFS (Depth First Search).
    Първо се създава графът на предметите, като се използва матрица на съседство, където ако има връзка от a към b, се отбелязва graph[a][b] = true.
    След това се извиква DFS върху всеки предмет, за да се провери дали има цикъл в графа. Ако има цикъл, не е възможно да се завърши взимането на предметите.
    Проверката за цикъл в графа се осъществява чрез DFS. Ако по време на DFS се намери връх, който е маркиран като посетен, но все още присъства в стека, то има цикъл в графа.
    
    Сложността на време на решението е O(N + M), където N е броят на предметите, а M е броят на условията (връзките между предметите).
*/

bool isCyclicUtil(int v, bool visited[], bool stack[], bool graph[][1000], int numCourses) {
    if (!visited[v]) {
        visited[v] = true;
        stack[v] = true;

        for (int i = 0; i < numCourses; i++) {
            if (graph[v][i]) {
                if (!visited[i] && isCyclicUtil(i, visited, stack, graph, numCourses))
                    return true;
                else if (stack[i])
                    return true;
            }
        }
    }
    stack[v] = false;
    return false;
}

bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize) {
    bool graph[1000][1000] = {false}; // Матрица за съхранение на връзките между предметите

    // Попълване на матрицата на съседство на графа
    for (int i = 0; i < prerequisitesSize; i++) {
        int a = prerequisites[i][0];
        int b = prerequisites[i][1];
        graph[a][b] = true;
    }

    bool visited[1000] = {false}; // Масив за отбелязване на посетените върхове
    bool stack[1000] = {false}; // Масив за отбелязване на върховете, които се намират на текущия път

    // Проверка за цикъл в графа
    for (int i = 0; i < numCourses; i++) {
        if (!visited[i] && isCyclicUtil(i, visited, stack, graph, numCourses))
            return false;
    }

    return true;
}

bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize)
{
    Graph* g = init_graph(numCourses);

    for(int i = 0; i < prerequisitesSize; i++) {
        addEdgeDirectional(g, prerequisites[i][0], prerequisites[i][1]);
    }

    // Perform DFS to check for cycles
    bool visited[numCourses];
    bool stack[numCourses];
    for (int i = 0; i < numCourses; i++) {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < numCourses; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(i, visited, stack, g->adjMatrix, numCourses))
                return false;
        }
    }

    return true;
}

bool canFinishR(int i, int* visited, DList* stack, Graph* g, int size) {
    if(visited[i] == 1) {
        return true; // Cycle detected
    }

    if(visited[i] == 2) {
        return false; // Already visited and processed
    }

    visited[i] = 1; // Mark as visiting
    insertBegin(stack, i);

    for(int j = 0; j < size; j++) {
        if(g->adjMatrix[i][j] && canFinishR(j, visited, stack, g, size)) {
            return true;
        }
    }

    visited[i] = 2; // Mark as processed
    popFront(stack);
    return false;
}

bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize) {
    Graph* g = init_graph(numCourses);

    for(int i = 0; i < prerequisitesSize; i++) {
        addEdgeDirectional(g, prerequisites[i][0], prerequisites[i][1]);
    }

    int* visited = (int*)malloc(numCourses * sizeof(int));
    DList* stack = init_dlist();

    for(int i = 0; i < numCourses; i++) {
        visited[i] = 0;
    }

    for(int i = 0; i < numCourses; i++) {
        if(visited[i] == 0 && canFinishR(i, visited, stack, g, numCourses)) {
            // Cycle detected
            free(visited);
            destroy_dlist(stack);
            return false;
        }
    }

    // No cycle detected
    free(visited);
    destroy_dlist(stack);
    return true;
}

int main() {
    // [[0,1]] true
    printf("%s [[0,1]]\n", (canFinish(2, (int *[]){(int[2]){0, 1}}, 1) ? "true" : "false"));
    // [[0,1],[1,0]] false
    printf("%s [[0,1],[1,0]]\n", canFinish(2, (int *[]){(int[2]){0, 1}, (int[2]){1, 0}}, 2) ? "true" : "false");
    // [[1,0],[2,1],[3,2],[4,3],[5,4],[6,5]] true
    printf("%s [[1,0],[2,1],[3,2],[4,3],[5,4],[6,5]]\n", canFinish(7, (int *[]){(int[2]){1, 0}, (int[2]){2, 1}, (int[2]){3, 2}, (int[2]){4, 3}, (int[2]){5, 4}, (int[2]){6, 5}}, 6) ? "true" : "false");
    // [[1,0],[2,1],[3,2],[4,3],[5,4],[6,5],[0,6]] false
    printf("%s [[1,0],[2,1],[3,2],[4,3],[5,4],[6,5],[0,6]]\n", canFinish(7, (int *[]
}