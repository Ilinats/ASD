#include <stdio.h>
#include "../vectors/vector.c"

int isPalindromeStep(vector_t *v, int start, int end) {
    if(start >= end) {
        return 1;
    }

    if(getAt(v, start) == getAt(v, end)) {
        return isPalindromeStep(v, start + 1, end - 1);
    } else
        return 0;
}

int isPalindrome(vector_t *v) {
    return isPalindromeStep(v, 0, getSize(v) - 1);
}

int main() {

    vector_t v;

    push_back(&v, 1);
    push_back(&v, 2);
    push_back(&v, 2);
    push_back(&v, 1);

    printf("%d\n", isPalindrome(&v));

    return 0;
}