#include <stdio.h>

int SumOfFirstN(int n) {
    if(n == 1)
        return 1;

    return SumOfFirstN(n-1) + n;
}

int main() {

    printf("%d\n", SumOfFirstN(5));

    return 0;
}