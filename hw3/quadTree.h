#ifndef QUADTREE_H
#define QUADTREE_H
#include "figure.h"

typedef struct node {
    float x1, y1, x2, y2;
    Node *childeren[4];
    Figure *figures[10];
    int figuresCount;
} Node;

#endif