#include <stdio.h>
#include <stdlib.h>

typedef struct vector_t {
    int *arr;
    int size;
    int capacity;
} vector_t;

vector_t *init_vector() {
    vector_t *v = (vector_t *)malloc(sizeof(vector_t));

    v->arr = NULL;
    v->size = 0;
    v->capacity = 0;

    return v;
}

void push_back(vector_t *v, int val) {
    v->size++;

    if(v->size > v->capacity)
        v->capacity = v->size * 2;

    else if(v->size <= v->capacity / 2)
        v->capacity /= 2;

    v->arr = (int *)realloc(v->arr, (v->size) * sizeof(int));
    v->arr[v->size - 1] = val;
}

void clear(vector_t *v) {
    free(v->arr);
    v->size = 0;
    v->capacity = 0;
}

void print_vector(vector_t *v) {
    for (int i = 0; i < v->size; i++)
        printf("%d ", v->arr[i]);

    printf("\n");
}

int binary_search(vector_t *v, int target, int start, int end) {
    if (start > end)
        return start;

    int mid = (start + end) / 2;

    if (v->arr[mid] == target)
        return mid;

    else if (v->arr[mid] > target)
        return binary_search(v, target, start, mid - 1);

    else
        return binary_search(v, target, mid + 1, end);
}

void insertion_sort(vector_t *v) {
    for (int i = 1; i < v->size; i++) {
        int key = v->arr[i];
        
        int j = i - 1;
        int index = binary_search(v, key, 0, j);

        for(; j >= index; j--) 
            v->arr[j+1] = v->arr[j];

        v->arr[index] = key;
    }
}

/* 
    В най-лошия случай - обратно сортиран масив, сложността ще бъде O(n^2), защото ще се извършва binary search О(logn), 
    както и преместване на всеки елемент, което е със сложност O(n) за всяка итерация, а итерациите са n на брой(от началото
    до края на масива).
    В най-добрия случай - подреден масив, сложността ще се свали само до O(n), защото не се налага да се разменят позиции на
    елементи в масива, а само да се обходи веднъж, но binary search-а все пак ще си има сложност O(logn).

    Обикновено Insertion sort има по-голяма сложност, тъй като обхожда масива веднъж за всички елементи О(n), и прави размени 
    със сложност O(n), което го прави сравнително бавен. Binary search-ът помага за сваляне на сложността, която идва от изместването 
    и размяната на елементи в масива, защото неговата сложност е по-малка. 

*/

int main() {
    vector_t *v = init_vector();

    push_back(v, 2);
    push_back(v, 0);
    push_back(v, -2);
    push_back(v, 7);
    push_back(v, 2);
    push_back(v, 6);
    push_back(v, -34);
    push_back(v, 112);
    push_back(v, 0);
    push_back(v, -134);
    push_back(v, 2);
    push_back(v, 2);
    push_back(v, 100);

    print_vector(v);
    insertion_sort(v);
    print_vector(v);

    free(v);
}
