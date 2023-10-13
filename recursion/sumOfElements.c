#include <stdio.h>
#include "../vectors/vector.c"

int SumOfElements(vector_t *v, int size) {
    if(size == 0) {
        return 0;
    }

    return SumOfElements(v, size - 1) + getAt(v, size - 1);
}

int main() {

    vector_t* v;
    v = init_vector();

    push_back(v, 3);
    push_back(v, 2);
    push_back(v, 2);
    push_back(v, 1);

    printf("%d\n", SumOfElements(v, getSize(v)));

    return 0;
}