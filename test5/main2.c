#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/hash.c"
#include "utils/pqueue.c"
#include "utils/graph_h.c"
#include "utils/dsu.c"

/*Даг се използва за задачи, в които трябва да визуализираме някакви връзки между различните данни.
Топологичното сортиране започва като намерим в кои nodove влизат други - тяхното inDegree. След това ги слагаме в queue
и си правим subset. Така на различните node-ove namirame vruzkata s vecvhe sushtestvuvat i go slagame w negoviq subset. 
Razlichnite subsetove obedinqvame s union join - po-kusiq slagame kum "korena" na po-dulgiq.*/


/*
    За улеснение за работата с HashMap с void* съм ви написал още две фунцкии:
    void setInt(HashMap *hash_map, char *key, int val);
    int getInt(HashMap *hash_map, char *key);

    С тях може лесно да сетвате и взимате int стойности от HashMap без да се занимавате с правилно алокиране и кастване.
    Така хем може да ползваме хешмапа със стрингове за граф, хем лесно работим с обикновенни числа.
*/

/*
    Дадени са:
    words - списък от думи с дължина n и всички думи в него са с
    дължина m
    forbidden_words - списък от думи с дължина с дължина k. k < n и
    всяка забранена дума се съдържа и в списъка words.
    Две думи са свързани ако се различават с максимум един символ.
    Например “hello” и “hallo”. Дадени са също така start и end думи. Да
    се намери най-кратката поредица от свързани думи, които започват
    от start и свършват в end и не съдържа в себе си забранени думи.
    Може да приемете, че start и end винаги ще съществуват в words
    масива. Ако не съществува такава поредица да се принтира -1. Ако
    имате време може да принтирате и самата поредица, но и
    дължината и достатъчно. Използвайте идеи от A* за да забързате
    вашия алгоритъм. Помислете каква би могла да ви бъде
    евристичната оценката и как бихте я запазили. Има ли нужда тя да
    се пресмята всеки път при обхождането?
    Напишете в коментар как сте решили задачата и каква е нейната
    сложност.
    Пример:
    words = [‘hot’, ‘fog’, ‘dog’, ‘pot’, ‘fot’, ‘dot’]
    forbidden_words = [‘dot’]
    start = dog
    end = pot
    answer: dog->fog->fot->pot , дължина 4
    dog->dot->pot би било по-кратко, но dot е забранена.

    Сложност: O(n^2 * m), където n е броя на думите, а m е дължината на всяка дума.
    С А* се опитвам да намеря най-краткия път между start и end, в който не влизат забранените думи и се различават с максимум 1 символ.
    Докато pq-то не е празно взимаме най-малкия елемент и ако е крайната дума спираме. За всяка съседна дума на текущата проверяваме дали можем да я посетим 
    и ако можем и е по-добра я добавяме в pq-то. При добавяне на дума в pq-то изчисляваме и нейния приоритет, който е сбор от dist и евристичната функция.
    Така най-малките думи минават първи и се намира най-краткия път.
    Сложността на добавяне и взимане на елемент от pq е O(logn), а сложността на добавяне на съседи на текущата дума е O(n).
    Сложността на A* е O(n^2 * m), където n е броя на думите, а m е дължината на всяка дума, заради изчисляването на евристичната функция.
    Всеки път при добавяне на дума в pq-то се изчислява разликата между нея и крайната дума, което е O(m).
    Така общо сложността е O(n^2 * m).
*/

int heuristic (char *a, char *b) {
    int diff = 0;
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] != b[i]) {
            diff++;
        }
    }
    return diff;
}

int word_path(char **words, int n, char **forbidden_words, int k, char *start, char *end)
{
    HashMap* forbidden = init_hash_map();
    
    for(int i = 0; i < k; i++)
        set(forbidden, forbidden_words[i], (void*)1);

    Graph *graph = init_graph();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            addEdge(graph, words[i], words[j], heuristic(words[i], words[j]));
    }

    PQueue *pq = init_pq();
    HashMap *dist = init_hash_map();
    HashMap *priorities = init_hash_map();

    for (int i = 0; i < n; i++) {
        setInt(dist, words[i], INT_MAX);
    }
    setInt(dist, start, 0);

    PQNode *el = (PQNode *)malloc(sizeof(PQNode));
    el->data = start;
    pqInsert(pq, el->data, 0);

    int count = n;

    while (pq->size > 0 && count-- > 0) {
        PQNode *current_element = (PQNode *)deleteMin(pq);
        char *current_word = (char *)current_element->data;
        int current_cost = getInt(dist, current_word);
        printf("%d\n", current_cost);
        printf("%s\n", current_word);

        if (strcmp(current_word, end) == 0) {
            free(current_element);
            printf("End: %d\n", current_cost);
            return current_cost;
        }

        VertexNode *neighbor = (VertexNode *)get(graph->adjList, current_word);
        printf("Neighbor: %s\n", neighbor->val);
        while (neighbor != NULL) {
            if(strcmp(neighbor->val, end) == 0){
                    int end = current_cost + neighbor->weight;
                    printf("End: %d\n", end);
                    if(end)
                        return end;
                    else 
                        return -1;
            }

            if (get(forbidden, neighbor->val) == NULL && neighbor->weight == 1) {
                printf("Inside");
                int new_cost = current_cost + neighbor->weight;
                if (new_cost < getInt(dist, neighbor->val)) {
                    setInt(dist, neighbor->val, new_cost);
                    PQNode *new_node = (PQNode *)malloc(sizeof(PQNode));
                    new_node->data = neighbor->val;
                    int priority = new_cost + heuristic(neighbor->val, end);
                    pqInsert(pq, new_node, priority);
                    printf("Priority: %d\n", priority);
                }
            }
            neighbor = neighbor->next;
            printf("Neighbor: %s\n", neighbor->val);
        }
        free(current_element);
    }

    return -1;
}

void test(int index, char **words, int n, char **forbidden_words, int k, char *start, char *end, int expected)
{
    int result = word_path(words, n, forbidden_words, k, start, end);
    printf("%d. Expected: %d, Result: %d %s\n", index, expected, result, expected == result ? "PASS" : "FAIL");
}

int main()
{
    // Забележка: това, че тестовете минават не значи, че сте направили коректно А*. Те ще минават и с обикновенно BFS.

    test(1, (char *[]){"hot", "fog", "dog", "pot", "fot", "dot"}, 6, (char *[]){"dot"}, 1, "dog", "pot", 3);
    test(2, (char *[]){"hot", "fog", "dog", "pot", "fot", "dot"}, 6, (char *[]){""}, 0, "dog", "pot", 2);
    test(3, (char *[]){"a", "q", "c"}, 3, (char *[]){"q"}, 1, "a", "c", 1);
    test(4, (char *[]){"ab", "rt", "gh"}, 3, (char *[]){""}, 0, "ab", "rt", -1);
    test(5, (char *[]){"hot", "fog", "dog", "pot", "fot", "dot"}, 6, (char *[]){"dot", "fog"}, 2, "dog", "fot", -1);
    test(6, (char *[]){"123456", "113456", "111456", "111156", "111116", "111111"}, 6, (char *[]){""}, 0, "123456", "111111", 5);
    // aaa -> baa -> bab
    test(7, (char *[]){"aaa", "aba", "abb", "baa", "bab", "bbb", "aab", "bba"}, 8, (char *[]){""}, 0, "aaa", "bab", 2);
    // aaa -> aba -> bba -> bbb -> bab
    test(8, (char *[]){"aaa", "aba", "abb", "baa", "bab", "bbb", "aab", "bba"}, 8, (char *[]){"baa", "aab"}, 2, "aaa", "bab", 4);

    return 0;
}
