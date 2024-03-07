#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>

DList *init_dlist()
{
    DList *l = (DList *)malloc(sizeof(DList));
    l->head = NULL;
    l->tail = NULL;

    return l;
}

NodeTree *createNode(int val)
{
    NodeTree *n = (NodeTree *)malloc(sizeof(NodeTree));
    n->value = val;
    n->next = NULL;
    n->prev = NULL;

    return n;
}

void insertBegin(DList *l, int val)
{
    NodeTree *n = createNode(val);

    if (l->head == NULL)
    {
        l->head = n;
        l->tail = n;

        return;
    }

    n->next = l->head;
    l->head->prev = n;
    l->head = n;
}

void insertEnd(DList *l, int val)
{
    NodeTree *n = createNode(val);

    if (l->tail == NULL)
    {
        l->head = n;
        l->tail = n;

        return;
    }

    n->prev = l->tail;
    l->tail->next = n;
    l->tail = n;
}

NodeTree *getAt(DList *l, int index)
{
    int i = 0;
    NodeTree *it = l->head;

    while (it != NULL && i < index)
    {
        it = it->next;
        i++;
    }

    if (i == index)
    {
        return it;
    }

    // handle error
    printf("Index out of range");
    exit(1);
}

int popFront(DList *l)
{
    if (l->head == NULL)
    {
        printf("Cannot pop from EMPTY\n");
        exit(1);
    }

    int val = l->head->value;
    NodeTree *head = l->head;

    if (l->head->next == NULL)
    {
        l->head = NULL;
        l->tail = NULL;
    }
    else
    {
        l->head->next->prev = NULL;
        l->head = l->head->next;
    }

    free(head);

    return val;
}

int pop(DList *l)
{
    if (l->tail == NULL)
    {
        printf("Cannot pop from EMPTY\n");
        exit(1);
    }

    int val = l->tail->value;
    NodeTree *tail = l->tail;

    if (l->tail->prev == NULL)
    {
        l->head = NULL;
        l->tail = NULL;
    }
    else
    {
        l->tail->prev->next = NULL;
        l->tail = l->tail->prev;
    }

    free(tail);

    return val;
}

void printDList(DList *l)
{
    if (l->head == NULL)
    {
        printf("EMPTY\n");
        return;
    }

    NodeTree *it = l->head;

    while (it != NULL)
    {
        printf("%d ", it->value);
        it = it->next;
    }

    printf("\n");
}

void printDListReverse(DList *l)
{
    if (l->tail == NULL)
    {
        printf("EMPTY\n");
        return;
    }

    NodeTree *it = l->tail;

    while (it != NULL)
    {
        printf("%d ", it->value);
        it = it->prev;
    }

    printf("\n");
}

void clear(DList *l)
{
    NodeTree *it = l->head;

    while (it != NULL)
    {
        NodeTree *tmp = it;
        it = it->next;
        free(tmp);
    }

    free(l);
}

void insertAfter(DList *l, NodeTree *it, NodeTree *val)
{
    if (it == l->tail)
    {
        insertEnd(l, val->value);
        return;
    }

    val->next = it->next;
    val->prev = it;
    it->next->prev = val;
    it->next = val;
}

void insertBefore(DList *l, NodeTree *it, NodeTree *val)
{
    if(it == l->head) {
        insertBegin(l, val->value);
        return;
    }

    val->next = it;
    val->prev = it->prev;
    it->prev->next = val;
    it->prev = val;
}

int removeAt(DList *l, NodeTree *val)
{
    if (val == l->head)
    {
        return popFront(l);
    }

    if (val == l->tail)
    {
        return pop(l);
    }

    val->prev->next = val->next;
    val->next->prev = val->prev;

    return val->value;
}

int search(DList *l, int val)
{
    NodeTree *it = l->head;

    while (it != NULL)
    {
        if (it->value == val)
        {
            return 1;
        }

        it = it->next;
    }

    return 0;
}