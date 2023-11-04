#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 10

int maxDigits(int * arr, int count) {
    int max = 0;

    for(int i = 0; i < count; i++) {
        int digits = 0;
        int num = arr[i];
        while(num > 0) {
            num /= 10;
            digits++;
        }
        if(digits > max) {
            max = digits;
        }
    }

    return (int)pow(10, (float)max - 1);;
}

void radixSortRec(int *arr, int position, int count) {
    if (position == 0 || count == 0) {
        return;
    }

    int **buckets = (int **)malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++) {
        buckets[i] = (int *)malloc(sizeof(int) * count);
    }

    int bucketCounts[10] = {0};

    for (int i = 0; i < count; i++) {
        int digit = arr[i] / position % 10;
        buckets[digit][bucketCounts[digit]++] = arr[i];
    }

    int index = 0;

    for (int i = 0; i < 10; i++) {
        radixSortRec(buckets[i], position / 10, bucketCounts[i]);

        for (int j = 0; j < bucketCounts[i]; j++) {
                arr[index++] = buckets[i][j];
            }
    }
}

void radix_sort(int* arr, unsigned int count) {
    if(count == 0) {
        return;
    }

    int max = maxDigits(arr, count);
    radixSortRec(arr, max, count);
}

int main() {

    int arr[SIZE] = {5, 5, 5, 5, 10, 22, 1009, 5, 3, 5};

    radix_sort(arr, SIZE);

    for(int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    };

    return 0;
}