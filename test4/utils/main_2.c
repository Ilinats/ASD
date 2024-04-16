#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph_matrix.h"
#include "dlist.h"

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
    
    Коментар обяснение: Когато в графа има цикъл, означава, че за да взема ключ за стая преди това трябва да съм взела 
    ключа за стаята, към която води той. Тоест взимането става невъзможно. За да се избегне това трябва да няма цикли в графа. 
    За да засека цикли в графа използвам DFS алгоритъм, като преди това превъщам масива в граф. За да проверя дали има цикъл 
    имам 3 състояния на visited - 0, ако не е, 1, ако е и обхождам съседите му с връзка, и 2, ако съм обходила съседите с връзка. 
    Ако случайно node, който обхождам сега, сочи към node, който вече трябва да е приключил с връзките(демек състояние 2), 
    означава, че имам цикъл и връща false. Когато започвам да обхождам node го слагам в stack-a, както и неговите връзки след това 
    и го попвам, ако достигне състояние 2. DFS има сложност O(V+E) и е това, което аз използвам в задачите си с няколко
    допълнителни проверки, тоест сложността е O(V+E). 

*/

bool canFinishR(int i, int* visited, DList* stack, Graph* g, int size) {
    if(visited[i] == 1)
        return true;

    if(visited[i] == 2)
        return false;

    visited[i] = 1;
    insertBegin(stack, i);

    for(int j = 0; j < size; j++) {
        if(g->adjMatrix[i][j] && canFinishR(j, visited, stack, g, size))
            return true;
    }

    visited[i] = 2;
    popFront(stack);

    return false;
}

bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize) {
    Graph* g = init_graph(numCourses);

    for(int i = 0; i < prerequisitesSize; i++)
        addEdgeDirectional(g, prerequisites[i][0], prerequisites[i][1]);

    int* visited = (int*)malloc(numCourses * sizeof(int));
    DList* stack = init_dlist();

    for(int i = 0; i < numCourses; i++)
        visited[i] = 0;

    for(int i = 0; i < numCourses; i++) {
        if(visited[i] == 0 && canFinishR(i, visited, stack, g, numCourses))
            return false;
    }

    free(visited);
    return true;
}

int main()
{
    // [[0,1]] true
    printf("%s [[0,1]]\n", (canFinish(2, (int *[]){(int[2]){0, 1}}, 1) ? "true" : "false"));
    // [[0,1],[1,0]] false
    printf("%s [[0,1],[1,0]]\n", canFinish(2, (int *[]){(int[2]){0, 1}, (int[2]){1, 0}}, 2) ? "true" : "false");
    // [[1,0],[2,1],[3,2],[4,3],[5,4],[6,5]] true
    printf("%s [[1,0],[2,1],[3,2],[4,3],[5,4],[6,5]]\n", canFinish(7, (int *[]){(int[2]){1, 0}, (int[2]){2, 1}, (int[2]){3, 2}, (int[2]){4, 3}, (int[2]){5, 4}, (int[2]){6, 5}}, 6) ? "true" : "false");
    // [[1,0],[2,1],[3,2],[4,3],[5,4],[6,5],[0,6]] false
    printf("%s [[1,0],[2,1],[3,2],[4,3],[5,4],[6,5],[0,6]]\n", canFinish(7, (int *[]){(int[2]){1, 0}, (int[2]){2, 1}, (int[2]){3, 2}, (int[2]){4, 3}, (int[2]){5, 4}, (int[2]){6, 5}, (int[2]){0, 6}}, 7) ? "true" : "false");
    // [[1,4],[2,4],[3,1],[3,2]] true
    printf("%s [[1,4],[2,4],[3,1],[3,2]]\n", canFinish(5, (int *[]){(int[2]){1, 4}, (int[2]){2, 4}, (int[2]){3, 1}, (int[2]){3, 2}}, 4) ? "true" : "false");
}