#include <stdio.h>

void PascalTriangle(int n) {
    if(n == 1) {
        printf("1\n");
        return;
    }

    PascalTriangle(n - 1);

    int prev = 1;
    printf("1 ");
    for(int i = 1; i < n; i ++) {
        printf("%d ", prev * (n - i) / i);
        prev = prev * (n - i) / i;
    }
    printf("\n");
}

int main() {

    PascalTriangle(5);

    return 0;
}