#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

List *init_list() {
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;

    return l;
}

Node *createNode(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = val;
    node->next = NULL;

    return node;
}

void insert(List *l, int val) {

    Node *node = createNode(val);
    node->next = l->head;
    l->head = node;
}

void clear(List *l) {
    Node *it = l->head;

    while (it != NULL) {
        Node *tmp = it;
        it = it->next;
        free(tmp);
    }

    free(l);
}

int getAt(List *l, int index) {
    int i = 0;
    Node *it = l->head;

    while (it != NULL && i < index) {
        it = it->next;
        i++;
    }

    if (i == index)
        return it->value;

    printf("Index out of range");
    exit(1);
}

void printList(List *l) {
    if (l->head == NULL) {
        printf("EMPTY\n");
        return;
    }

    Node *it = l->head;

    while (it != NULL) {
        printf("%d ", it->value);
        it = it->next;
    }

    printf("\n");
}