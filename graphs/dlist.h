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

NodeTree *getAt(DList *, int);
void clear(DList *);
int pop(DList *);
void printDList(DList *);
void printDListReverse(DList *);
int popFront(DList *);

void insertAt(DList *, NodeTree *, NodeTree *);

NodeTree *createNode(int val);
void insertBefore(DList *l, NodeTree *it, NodeTree *val);
void insertAfter(DList *l, NodeTree *it, NodeTree *val);
int removeAt(DList *l, NodeTree *val);

#endif