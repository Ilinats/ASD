#include "stdio.h"
#include "vector.c"

int swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {

    vector_t *v = init_vector();
    int currNum;

    push_back(v, 3);
    push_back(v, 2);
    push_back(v, 6);
    push_back(v, 1);
    push_back(v, 5);
    push_back(v, 4);

    for (int i = 0; i < getSize(v) - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < getSize(v); j++) {
            if (getAt(v, j) < getAt(v, minIndex)) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            swap(&v->arr[i], &v->arr[minIndex]);
        }
    }

    printVector(v);

    return 0;
}