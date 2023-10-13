#include <stdio.h>

int power(int n, int p) {
    if(p == 0)
        return 1;

    return power(n, p-1) * n;
}

int main() {

    printf("%d\n", power(2, 3));
    
    return 0;
}