#include <stdlib.h>
#include "figure.h"
#include "quadTree.h"
#include <stdio.h>
#include <math.h>

Node *createNode(float xMin, float yMin, float xMax, float yMax, Node *parent) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->xMin = xMin;
    node->yMin = yMin;
    node->xMax = xMax;
    node->yMax = yMax;
    node->figuresCount = 0;
    node->children = NULL;
    node->figures = NULL;
    node->parent = parent;

    return node;
}

void allocateChildren(Node *node) {
    if(node->children)
        return;

    node->children = (Node **) malloc(sizeof(Node *) * 4);

    float xMid = (node->xMin + node->xMax) / 2;
    float yMid = (node->yMin + node->yMax) / 2;

    node->children[0] = createNode(node->xMin, yMid, xMid , node->yMax, node);
    node->children[1] = createNode(xMid, yMid, node->xMax, node->yMax, node);
    node->children[2] = createNode(node->xMin, node->yMin, xMid , yMid, node);
    node->children[3] = createNode(xMid, node->yMin, node->xMax, yMid, node);
}

int isInside(Figure *fig, Node *n) {
    return fig->x >= n->xMin && fig->x <= n->xMax && fig->y >= n->yMin && fig->y <= n->yMax;
}

int insertFigure(Node *node, Figure *figure) {
    if(!isInside(figure, node))
        return 0;

    if(node->children) {
        for(int i=0; i<4; i++) {
            if(insertFigure(node->children[i], figure))
                break;
        }
    }
    else {
        if(node->figuresCount < 10) {
            if(!node->figures)
                node->figures = (Figure **) malloc(sizeof(Figure *) * 10);
            node->figures[node->figuresCount++] = figure;
        }
        else {
            allocateChildren(node);

            for(int i=0; i<node->figuresCount; i++)
                insertFigure(node, node->figures[i]);

            insertFigure(node, figure);

            node->figuresCount = 0;
            free(node->figures);
            node->figures = NULL;
        }
    }
}

Node *build_tree(Figure **figures, int figuresCount) {
    Node *root = createNode(-1000, -1000, 1000, 1000, NULL);

    for (int i = 0; i < figuresCount; i++)
        insertFigure(root, figures[i]);

    return root;
}

void printTree(Node *node, int depth) {
    if(node == NULL)
        return;

     printf("\n%*sNode: (%f, %f)(%f, %f)", depth*4, "", node->xMin, node->yMin, node->xMax, node->yMax);

    if(node->children) {
        for(int i = 0; i < 4; i++)
            printTree(node->children[i], depth + 1);
    } else if(node->figures) {
        for(int i = 0; i < node->figuresCount; i++)
            printf("\n%*s - %s(%f, %f)", depth*4, "", node->figures[i]->name, node->figures[i]->x, node->figures[i]->y);

        printf("\n");
    }
}

int isNodeInside(Node *child, Node *parent) {
    if(child == NULL || parent == NULL || child == parent)
        return 0;

    return child->xMin >= parent->xMin && child->xMax <= parent->xMax 
        && child->yMin >= parent->yMin && child->yMax <= parent->yMax;
}

int isNeighbor(Node *node1, Node *node2) {
    if(node1 == NULL || node2 == NULL || node1 == node2)
        return 0;

    return (node1->xMin == node2->xMax && !(node1->yMin > node2->yMax || node1->yMax < node2->yMin))
        || (node1->xMax == node2->xMin && !(node1->yMin > node2->yMax || node1->yMax < node2->yMin))
        || (node1->yMin == node2->yMax && !(node1->xMin > node2->xMax || node1->xMax < node2->xMin))
        || (node1->yMax == node2->yMin && !(node1->xMin > node2->xMax || node1->xMax < node2->xMin));
}

void checkSelfForOverlaps(Node *node, Pair **pairs, int *pairsCount) {
    if(node->figures)
        for(int i = 0; i < node->figuresCount; i++) {
            for(int j = i+1; j < node->figuresCount; j++) {
                if(overlap(node->figures[i], node->figures[j])) {
                    if(*pairs == NULL)
                        *pairs = (Pair *) malloc(sizeof(Pair));
                    else
                        *pairs = (Pair *) realloc(*pairs, sizeof(Pair) * (*pairsCount + 1));

                    (*pairs)[*pairsCount].figure1 = node->figures[i];
                    (*pairs)[*pairsCount].figure2 = node->figures[j];
                    (*pairsCount)++;
                }
            }
        }
}

void checkForOverlaps(Node *node1, Node *node2, Pair **pairs, int *pairsCount) {
    if(node1->figures && node2->figures)
        for(int i = 0; i < node1->figuresCount; i++) {
            for(int j = 0; j < node2->figuresCount; j++) {
                if(overlap(node1->figures[i], node2->figures[j])) {
                    if(*pairs == NULL)
                        *pairs = (Pair *) malloc(sizeof(Pair));
                    else
                        *pairs = (Pair *) realloc(*pairs, sizeof(Pair) * (*pairsCount + 1));

                    (*pairs)[*pairsCount].figure1 = node1->figures[i];
                    (*pairs)[*pairsCount].figure2 = node2->figures[j];
                    (*pairsCount)++;
                }
            }
        }
}

void findOverlaps(Node *target, Node *node, Pair **pairs, int *pairsCount) {
    if(node == NULL)
        return;

    if(node->children) {
        for(int i = 0; i < 4; i++) {
            if(isNeighbor(target, node->children[i]) || isNodeInside(target, node->children[i]))
                findOverlaps(target, node->children[i], pairs, pairsCount);
        }
    }
    else {
        if(isNeighbor(target, node))
            checkForOverlaps(target, node, pairs, pairsCount);
    }
}

void printPairs(Pair *pairs, int pairsCount) {
    printf("\nPairs:\n");
    for(int i = 0; i < pairsCount; i++)
        printf("%d) %s %s\n", i+1, pairs[i].figure1->name, pairs[i].figure2->name);
}

void printOverlaps(Node *node, Node *root) {
    Pair *pairs = NULL;
    int pairsCount = 0;
    findOverlaps(node, root, &pairs, &pairsCount);
    checkSelfForOverlaps(node, &pairs, &pairsCount);  

    if(pairsCount == 0)
        printf("\nNo overlaps found.\n");
    else
        printPairs(pairs, pairsCount);

    free(pairs);
}

void freeTree(Node *node) {
    if(node == NULL)
        return;

    if(node->children) {
        for(int i = 0; i < 4; i++)
            freeTree(node->children[i]);
            
        free(node->children);
    }

    if(node->figures) {
        for(int i = 0; i < node->figuresCount; i++) {
            free(node->figures[i]->name);
            free(node->figures[i]);
        }
        free(node->figures);
    }

    free(node);
}