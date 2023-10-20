#include <stdio.h>
#include "vector.c"

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(vector_t *v, int start, int end)
{
    int i = start;
    int j = start;
    int pivot = getAt(v, end);

    while(getAt(v, j) < pivot)
    {
        j++;
        i++;
    }

    for(; i < end; i++) {
        if(getAt(v, i) < pivot) {
            swap(&v->arr[i], &v->arr[j]);
            j++;
        }
    }

    swap(&v->arr[j], &v->arr[end]);
    return j;
}

void quicksortR(vector_t *v, int start, int end)
{
    if (start >= end)
    {
        return;
    }

    int mid = partition(v, start, end);
    quicksortR(v, start, mid - 1);
    quicksortR(v, mid + 1, end);
}

void quicksort(vector_t *v)
{
    quicksortR(v, 0, getSize(v) - 1);
}

int main()
{
    vector_t *v = init_vector();

    push_back(v, 0);
    push_back(v, -3);
    push_back(v, 5);
    push_back(v, 3);
    push_back(v, 2);
    push_back(v, 12);
    push_back(v, -10);
    push_back(v, 3);
    push_back(v, 7);
    push_back(v, 4);
    push_back(v, -5);
    push_back(v, 3);

    quicksort(v);
    printVector(v);

    return 0;
}