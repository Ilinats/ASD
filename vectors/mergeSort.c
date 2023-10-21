#include <stdio.h>
#include "vector.c"

void merge(int * arr, int left[], int right[], int leftSize, int rightSize) {
    int leftIndex = 0;
    int rightIndex = 0; 
    int vectorIndex = 0;

    while (leftIndex < leftSize && rightIndex < rightSize) {
        
        if (left[leftIndex] <= right[rightIndex]) {
            arr[vectorIndex] = left[leftIndex];
            leftIndex++;
        } else {
            arr[vectorIndex] = right[rightIndex];
            rightIndex++;
        }
        vectorIndex++;
    }

    while (leftIndex < leftSize) {
        arr[vectorIndex] = left[leftIndex];
        leftIndex++;
        vectorIndex++;
    }

    while (rightIndex < rightSize) {
        arr[vectorIndex] = right[rightIndex];
        rightIndex++;
        vectorIndex++;
    }
}

void mergeSort(int * arr, int size) {
    if (size <= 1) {
        return;
    }

    int mid = size / 2;

    int left[mid];
    int right[size - mid];

    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    mergeSort(left, mid);
    mergeSort(right, size - mid);

    merge(arr, left, right, mid, size - mid);
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

    mergeSort(v->arr, getSize(v));
    printVector(v);

    return 0;
}