#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

#define MSB 64

void swap(long a[], int i, int j) {
    long tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int isBitSet(long x, int k) {
    int set = (x & (1L << (k - 1))) != 0;

    // Invert the signed bit so that all positive integers come after negative ones
    return (k == MSB) != set;
}

void sort(long a[], int d, int lo, int hi) {
    if (hi < lo || d < 1) return;

    int left = lo - 1;
    int right = hi + 1;

    for (int i = left + 1; i < right; ) {
        if (isBitSet(a[i], d)) {
            swap(a, i, --right);
        } else {
            left++;
            i++;
        }
    }
    sort(a, d - 1, lo, left);
    sort(a, d - 1, right, hi);
}

Pair* twoSum(long a[], long sum, int n) {
    sort(a, MSB, 0, n - 1);

    int i = 0;
    int j = n - 1;

    while (i < j) {
        long t = a[i] + a[j];
        if (t == sum) {
            Pair* result = (Pair*)malloc(sizeof(Pair));
            result->first = i;
            result->second = j;
            return result;
        } else if (t < sum) {
            i++;
        } else {
            j--;
        }
    }
    return NULL;
}

int main() {
    long a[] = {3, -5, 2, 8, -7, 1};
    int n = sizeof(a) / sizeof(a[0]);
    long sum = 10;

    Pair* result = twoSum(a, sum, n);

    if (result != NULL) {
        printf("Indices: %d, %d\n", result->first, result->second);
        free(result);
    } else {
        printf("No such pair found\n");
    }

    for(int i = 0; i < n; i++) {
        printf("%ld ", a[i]);
    }

    return 0;
}
