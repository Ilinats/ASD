#ifndef DLIST_H
#define DLIST_H

typedef struct NodeTree
{
    int value;
    struct NodeTree *next;
    struct NodeTree *prev;
} NodeTree;

typedef struct DList
{
    NodeTree *head;
    NodeTree *tail;
} DList;

DList *init_dlist();
void insertBegin(DList *, int);
void insertEnd(DList *, int);
int pop(DList *);

NodeTree *createNode(int val);
void insertBefore(DList *l, NodeTree *it, NodeTree *val);
void insertAfter(DList *l, NodeTree *it, NodeTree *val);

#endif