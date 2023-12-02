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

BinaryHeap *heapify(int *arr, int size) {
    BinaryHeap *heap = createHeap();

    for(int i = size / 2 - 1; i >= 0; i--) {
        int temp = i; // индекс на родителя

        while(2 * temp + 1 < size) {
            int child1 = 2 * temp + 1;

            if(child1 + 1 < size && arr[child1 + 1] > arr[child1])  // проверка дали има второ дете и дали е по-голямо от първото
                child1++;

            if(arr[temp] < arr[child1]) {   // проверка дали родителят е по-малък от по-голямото дете и ако е разменяме стойностите им
                int tmp = arr[temp];
                arr[temp] = arr[child1];
                arr[child1] = tmp;
                temp = child1; // преместване на индекса на родителя на по-голямото дете
            } else
                break;
        }
    }

    for(int i = 0; i < size; i++)
        push_back(heap, arr[i]);

    return heap;
};

void siftDown(BinaryHeap *heap, int index, int size) {
    int temp = heap->arr[index];
    heap->arr[index] = heap->arr[0];
    heap->arr[0] = temp; // размяна на стойностите на първия елемент с последния

    heap = heapify(heap->arr, size); // пренареждане на масива до heap
}

BinaryHeap *heapSort(int *arr, int count) {
    BinaryHeap *heap = heapify(arr, SIZE);
    int size = heap->size;

    for(int i = count - 1; i > 0; i--){
        siftDown(heap, i, --size); // смяна на последния незамразен елемент с първия и пренареждане на масива до heap
        printHeap(heap);
    }

    return heap;
}

int main() {
    int arr[SIZE] = {3, 18, 39, 5, 6, 33, 90, 23487, 1234, 12352, 800,  700, 500, 400, 900, 1909000};

    BinaryHeap *heap = heapSort(arr, SIZE);

    return 0;
}