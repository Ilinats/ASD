#include <stdio.h>

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

    return max;
}

int getDigit(int num, int position) {
    for (int i = 0; i < position - 1; i++) {
        num /= 10;
    }
    return num % 10;
}

void radixSortRec(int *arr, int position, int count) {
    if(position == 0 || count == 0) {
        return;
    }

    int buckets[10][10] = {0};
    int bucketCounts[10] = {0};

    for(int i = 0; i < count; i++) {
        int digit = getDigit(arr[i], position);
        buckets[digit][bucketCounts[digit]] = arr[i];
        bucketCounts[digit]++;
    }

    for(int i = 0; i < 10; i++) {
        if(bucketCounts[i])
            radixSortRec(buckets[i], position - 1, bucketCounts[i]);
    }

    int index = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < bucketCounts[i]; j++) {
            arr[index] = buckets[i][j];
            index++;
        }
    }
}

void radix_sort(int* arr, unsigned int count) {
    if(count == 0) {
        return;
    }

    int negative[10] = {0};
    int positive[10] = {0};
    int negCount = 0;
    int posCount = 0;

    for(int i = 0; i < count; i++) {
        if(arr[i] < 0) {
            negative[negCount] = arr[i];
            negCount++;
        } else {
            positive[posCount] = arr[i];
            posCount++;
        }
    }

    radixSortRec(negative, maxDigits(negative, negCount), negCount);
    radixSortRec(positive, maxDigits(positive, posCount), posCount);

    for(int i = 0; i < negCount; i++) {
        arr[i] = negative[negCount - i - 1];
    }

    for(int i = 0; i < posCount; i++) {
        arr[i + negCount] = positive[i];
    }
}

int main() {

    int arr[9] = {5, -23, 45, 43, -10, 22, -55, 155, -125};
    printf("%d\n", maxDigits(arr, 9));

    radix_sort(arr, 9);

    for(int i = 0; i < 9; i++) {
        printf("%d ", arr[i]);
    };

    return 0;
}