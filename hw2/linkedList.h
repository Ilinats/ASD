#ifndef LIST_H
#define LIST_H

typedef struct node {
    int value;
    struct Node *next;
} Node;

typedef struct list {
    Node *head;
} List;

List *init_list();
void insert(List *, int);
int getAt(List *, int);
void clear(List *);
void printList(List *);

#endif