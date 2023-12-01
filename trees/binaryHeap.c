#include <stdio.h>
#include <stdlib.h>
#define SIZE 16

typedef struct BinaryHeap {
    int *arr;
    int size;
} BinaryHeap;

BinaryHeap *createHeap() {
    BinaryHeap *tmp = (BinaryHeap *)malloc(sizeof(BinaryHeap));
    tmp->arr = NULL;
    tmp->size = 0;
    return tmp;
}

void push_back(BinaryHeap *heap, int val) {
    heap->size++;

    heap->arr = (int *)realloc(heap->arr, (heap->size) * sizeof(int));
    heap->arr[heap->size - 1] = val;
}

void printHeap(BinaryHeap *heap) {
    for(int i = 0; i < heap->size; i++)
        printf("%d ", heap->arr[i]);

    printf("\n");
}

BinaryHeap *heapify(int *arr) {
    BinaryHeap *heap = createHeap();
    heap->arr = arr;
    heap->size = SIZE;

    for(int i = SIZE / 2 - 1; i >= 0; i--) {
        int temp = i;

        while(2 * temp + 1 < SIZE) {
            int child1 = 2 * temp + 1;

            if(child1 + 1 < SIZE && arr[child1 + 1] > arr[child1])
                child1++;

            if(arr[temp] < arr[child1]) {
                int tmp = arr[temp];
                arr[temp] = arr[child1];
                arr[child1] = tmp;
                temp = child1;
            } else
                break;
        }
    }

    printHeap(heap);

    return heap;
};

void siftUp (BinaryHeap *heap, int index) {
}

int main() {
    int arr[SIZE] = {3, 18, 39, 5, 6, 33, 90, 23487, 1234, 12352, 800,  700, 500, 400, 900, 1909000};

    BinaryHeap *heap = heapify(arr);
    push_back(heap, 1000000);

    return 0;
}