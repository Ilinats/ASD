#include "xorlist.h"
#include <stdio.h>

int main() {

    Node *head = initList();

    pushFront(&head, 1);
    pushFront(&head, -9);
    pushFront(&head, 8);
    pushFront(&head, 4);
    pushFront(&head, 2);
    pushBack(&head, 3);
    pushBack(&head, 5);

    printForward(head);
    printBackward(head);

    freeList(&head);
}