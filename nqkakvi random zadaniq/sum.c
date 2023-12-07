/*Даден е масив А[1,2,..., п] от цели числа и цяло число т. Предложете алгоритъм със сложност по време O(n √n), който връща
1, ако има два различни елемента на А със сума т,
0, ако няма такива елементи.*/

#include <stdio.h>
#define SIZE 10

void merge(int *arr, int left[], int right[], int leftSize, int rightSize) {
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

void mergeSort(int *arr, int size) {
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

int main() {

    int arr[SIZE] = {3, 5, 12, 54, 6, 34, 0, 7, 13, 76};
    mergeSort(arr, SIZE);

    for(int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}