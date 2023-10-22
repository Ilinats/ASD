#include <stdio.h>
#define SIZE 3

void allSumsRec(int *arr, int index, int sum) {
    if(index == SIZE) {
        printf("%d\n", sum);
        return;
    }

    allSumsRec(arr, index+1, sum);
    allSumsRec(arr, index+1, sum + arr[index]);
}

int main() {

    int arr[SIZE] = {5, 6, 7};

    allSumsRec(arr, 0, 0);
    
    return 0;
}