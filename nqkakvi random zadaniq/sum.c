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

int binarySearch(int *arr, int target, int start, int end) {
    if(start > end) {
        return 0;
    };

    int mid = (start + end) / 2;

    if(arr[mid] == target)
        return 1;

    else if(arr[mid] > target)
        return binarySearch(arr, target, start, mid - 1);

    else
        return binarySearch(arr, target, mid + 1, end);
}

int checkSum(int *arr, int size, int target) {
    for(int i = 0; i < size; i++) {
        if(binarySearch(arr, target - arr[i], 0, size - 1))
            return 1;
    }
    return 0;
}

int main() {

    int arr[SIZE] = {3, 5, 12, 54, 6, 34, 0, 7, 13, 76};
    mergeSort(arr, SIZE);

    for(int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n%d", checkSum(arr, SIZE, 11));
    printf("\n%d", checkSum(arr, SIZE, 111));
    printf("\n%d", checkSum(arr, SIZE, 103));

    return 0;
}