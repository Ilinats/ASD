#include <stdio.h>
#include "vector.h"
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(vector_t *v, int start, int end)
{
    int i = start;
    int j = end;
    int pivot = getAt(v, end);

    printVector(v);
    while (1)
    {
        while (getAt(v, i) < pivot)
            i++;

        while (getAt(v, j) > pivot)
            j--;

        if (i >= j)
            return i;

        swap(&(v->arr[i]), &(v->arr[j]));
        
        i++;
        j--;
    }
}

void quicksortR(vector_t *v, int start, int end)
{
    if (start >= end)
    {
        return;
    }

    int mid = partition(v, start, end);
    quicksortR(v, start, mid - 1);
    quicksortR(v, mid, end);
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