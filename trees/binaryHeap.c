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

void resize(BinaryHeap *heap, int newCapacity) {
    int *tmp = (int *)realloc(heap->arr, newCapacity * sizeof(int));
    if (tmp == NULL)
        exit(1);

    heap->arr = tmp;
    heap->size = newCapacity;
}


void push_back(BinaryHeap *heap, int val) {
    resize(heap, heap->size+1);

    heap->arr[heap->size-1] = val;
}

void printHeap(BinaryHeap *heap) {
    for(int i = 0; i < heap->size; i++)
        printf("%d ", heap->arr[i]);

    printf("\n");
}

BinaryHeap *heapify(int *arr) {
    BinaryHeap *heap = createHeap();

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

    for(int i = 0; i < SIZE; i++)
        push_back(heap, arr[i]);

    printHeap(heap);

    return heap;
};

void siftDown(BinaryHeap *heap, int index, int size) {
    int temp = heap->arr[index];
    heap->arr[index] = heap->arr[0];
    heap->arr[0] = temp;

    int tempIndex = 0;

    while(2 * tempIndex + 1 < size) {
        int child1 = 2 * tempIndex + 1;

        if(child1 + 1 < size && heap->arr[child1 + 1] > heap->arr[child1])
            child1++;

        if(heap->arr[tempIndex] < heap->arr[child1]) {
            int tmp = heap->arr[tempIndex];
            heap->arr[tempIndex] = heap->arr[child1];
            heap->arr[child1] = tmp;
            tempIndex = child1;
        } else
            break;
    }
}

BinaryHeap *heapSort(int *arr, int count) {
    BinaryHeap *heap = heapify(arr);
    int size = heap->size;

    for(int i = count - 1; i > 0; i--){
        siftDown(heap, i, --size);
        printHeap(heap);
    }

    return heap;
}

int main() {
    int arr[SIZE] = {3, 18, 39, 5, 6, 33, 90, 23487, 1234, 12352, 800,  700, 500, 400, 900, 1909000};

    BinaryHeap *heap = heapSort(arr, SIZE);
    printHeap(heap);

    return 0;
}