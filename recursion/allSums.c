#include <stdio.h>
#define SIZE 3

void allSumsRec(int *arr, int index, int sum) {
    if(index == SIZE) {
        printf("0, %d", sum);
        return;
    }

    printf("%d, ", arr[index]);
    sum += arr[index];

    for(int i = index+1; i < SIZE; i ++) {
        printf("%d, ", arr[i]+ arr[index]);
    }

    allSumsRec(arr, index+1, sum);
}

int main() {

    int arr[SIZE] = {5, 6, 7};

    allSumsRec(arr, 0, 0);
    
    return 0;
}