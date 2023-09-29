#include "stdio.h"
#include "vector.c"

void sortedThird(vector_t *v1, vector_t *v2, vector_t *joint) {

    int index1 = 0;
    int index2 = 0;
    
    while(index1 < getSize(v1) && index2 < getSize(v2)) {
        if (getAt(v1, index1) < getAt(v2, index2)) {
            push_back(joint, getAt(v1, index1));
            index1++;
        } else {
            push_back(joint, getAt(v2, index2));
            index2++;
        }
    }

    while(index1 < getSize(v1)) {
        push_back(joint, getAt(v1, index1));
        index1++;
    }

    while(index2 < getSize(v2)) {
        push_back(joint, getAt(v2, index2));
        index2++;
    }
}

int main() {

    vector_t *v1 = init_vector();
    vector_t *v2 = init_vector();
    vector_t *v3 = init_vector();

    push_back(v1, 3);
    push_back(v1, 5);
    push_back(v1, 6);
    push_back(v2, 1);
    push_back(v2, 2);
    push_back(v2, 4);

    sortedThird(v1, v2, v3);

    printVector(v3);

    return 0;
}