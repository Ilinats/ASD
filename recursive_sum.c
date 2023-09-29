#include "stdio.h"
#include "vector.c"

int vectorSum(vector_t *v, int currentIndex) {
    if (currentIndex == getSize(v)) {
        return 0;
    }

    return getAt(v, currentIndex) + vectorSum(v, currentIndex + 1);
}

int main() {

    vector_t *v = init_vector();
    int currNum;

    push_back(v, 5);
    push_back(v, 6);
    push_back(v, 7);

    printf("%d\n", vectorSum(v, 0)); // should print 18

    return 0;
}