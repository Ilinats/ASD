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