#include "xorlist.h"
#include <stdlib.h>
#include <stdio.h>

Node* initList() {
    return NULL;
}

Node *XOR(Node *a, Node *b) {
    return (Node *)((uintptr_t)(a) ^ (uintptr_t)(b));
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->data = data;
    newNode->npx = NULL;
    return newNode;
}

void pushFront(Node **list, int data) {
    Node *newNode = createNode(data);
    newNode->npx = *list;

    if (*list != NULL) {
        (*list)->npx = XOR(newNode, (*list)->npx);
    }

    *list = newNode;
}

void pushBack(Node **list, int data) {
    Node *newNode = createNode(data);
    Node *curr = *list;
    Node *prev = NULL;
    Node *next;

    if (*list == NULL) {
        *list = newNode;
        return;
    }

    while (curr != NULL) {
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }

    newNode->npx = prev;
    prev->npx = XOR(newNode, prev->npx);
}

void printList(Node *list) {
    Node *curr = list;
    Node *prev = NULL;
    Node *next;

    while (curr != NULL) {
        printf("%d ", curr->data);
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
}

void freeList(Node **list) {
    Node *curr = *list;
    Node *prev = NULL;
    Node *next;

    while (curr != NULL) {
        next = XOR(prev, curr->npx);
        free(curr);
        prev = curr;
        curr = next;
    }
    *list = NULL;
}