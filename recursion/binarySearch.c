#include <stdio.h>
#include "../vectors/vector.c"

int BinarySearch(vector_t *v, int target, int start, int end) {
    if(start > end) {
        return -1;
    }

    return getAt(v, (start + end) / 2) == target ? (start + end) / 2 : getAt(v, (start + end) / 2) > target ? BinarySearch(v, target, start, (start + end) / 2 - 1) : BinarySearch(v, target, (start + end) / 2 + 1, end);

}
    

int main() {

    vector_t* v;
    v = init_vector();

    push_back(v, 1);
    push_back(v, 2);
    push_back(v, 3);
    push_back(v, 4);
    push_back(v, 5);
    push_back(v, 6);
    push_back(v, 7);
    

    printf("%d\n", BinarySearch(v, 9, 0, getSize(v) - 1));

    return 0;
}