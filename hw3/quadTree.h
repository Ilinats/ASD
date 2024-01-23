#ifndef QUADTREE_H
#define QUADTREE_H
#include "figure.h"

typedef struct node {
    float xMin; 
    float yMin;
    float xMax;
    float yMax;
    struct node **children;
    Figure **figures;
    int figuresCount;
    struct node *parent;
} Node;

typedef struct pair {
    Figure *figure1;
    Figure *figure2;
} Pair;

void allocateChildren(Node *node);
int isInside(Figure *fig, Node *n);
int insertFigure(Node *node, Figure *figure);
Node *build_tree(Figure **figures, int figuresCount);
void printTree(Node *node, int depth);
int isNodeInside(Node *child, Node *parent);
int isNeighbor(Node *node1, Node *node2);
void checkSelfForOverlaps(Node *node, Pair **pairs, int *pairsCount);
void checkForOverlaps(Node *node1, Node *node2, Pair **pairs, int *pairsCount);
void findOverlaps(Node *target, Node *node, Pair **pairs, int *pairsCount);
void printPairs(Pair *pairs, int pairsCount);
void printOverlaps(Node *node, Node *root);
void freeTree(Node *node);

#endif