#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    Point min;
    Point max;
} BoundingBox;

typedef enum{
    CIRCLE,
    SQUARE
} FigureType;

typedef struct {
    Point center;
    FigureType type;
    union {
        int sideLen;
        int radius;
    };
    char *name;
} Figure;

typedef struct node {
    BoundingBox box;
    struct node **children;
    Figure **figures;
    int figuresCount;
    struct node *parent;
} Node;

typedef struct pair {
    Figure *figure1;
    Figure *figure2;
} Pair;

Figure *initFigure(float x, float y) {
    Figure *figure = (Figure *)malloc(sizeof(Figure));
    figure->center.x = x;
    figure->center.y = y;

    return figure;
}

Figure *createCircle(float x, float y, int radius) {
    static int count = 0;

    Figure *circle = initFigure(x, y);
    circle->radius = radius;
    circle->type = CIRCLE;

    circle->name = (char *)malloc(10);
    snprintf(circle->name, 10, "%s%d", "circ", ++count);
    return circle;
}

Figure *createSquare(float x, float y, int sideLen) {
    static int count = 0;

    Figure *square = initFigure(x, y);
    square->sideLen = sideLen;
    square->type = SQUARE;

    square->name = (char *)malloc(10);
    snprintf(square->name, 10, "%s%d", "sqr", ++count);
    return square;
}

Node *createNode(float xMin, float yMin, float xMax, float yMax, Node *parent) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->box.min.x = xMin;
    node->box.min.y = yMin;
    node->box.max.x = xMax;
    node->box.max.y = yMax;
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

    float xMid = (node->box.min.x + node->box.max.x) / 2;
    float yMid = (node->box.min.y + node->box.max.y) / 2;

    node->children[0] = createNode(node->box.min.x, yMid, xMid , node->box.max.y, node);
    node->children[1] = createNode(xMid , yMid, node->box.max.x, node->box.max.y, node);
    node->children[2] = createNode(node->box.min.x, node->box.min.y, xMid , yMid, node);
    node->children[3] = createNode(xMid , node->box.min.y, node->box.max.x, yMid, node);
}

int isInside(Point *p, BoundingBox *box) {
    return p->x >= box->min.x && p->x <= box->max.x && p->y >= box->min.y && p->y <= box->max.y;
}

int insertFigure(Node *node, Figure *figure) {
    if(!isInside(&figure->center, &node->box))
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

     printf("\n%*sNode: (%f, %f)(%f, %f)", depth*4, "", node->box.min.x, node->box.min.y, node->box.max.x, node->box.max.y);

    if(node->children) {
        for(int i = 0; i < 4; i++)
            printTree(node->children[i], depth + 1);
    } else if(node->figures) {
        for(int i = 0; i < node->figuresCount; i++)
            printf("\n%*s - %s(%f, %f)", depth*4, "", node->figures[i]->name, node->figures[i]->center.x, node->figures[i]->center.y);
    }
}

int circlesOverlap(Figure *fig1, Figure *fig2) {
    float distance = sqrt(pow(fig1->center.x - fig2->center.x, 2) + pow(fig1->center.y - fig2->center.y, 2));
    return distance <= fig1->radius + fig2->radius;
}

int squaresOverlap(Figure *fig1, Figure *fig2) {
    float x1 = fig1->center.x - fig1->sideLen / 2;
    float x2 = fig1->center.x + fig1->sideLen / 2;
    float y1 = fig1->center.y - fig1->sideLen / 2;
    float y2 = fig1->center.y + fig1->sideLen / 2;

    float x3 = fig2->center.x - fig2->sideLen / 2;
    float x4 = fig2->center.x + fig2->sideLen / 2;
    float y3 = fig2->center.y - fig2->sideLen / 2;
    float y4 = fig2->center.y + fig2->sideLen / 2;

    return !(x2 < x3 || x4 < x1 || y2 < y3 || y4 < y1);
}

int circleAndSquareOverlap(Figure *circle, Figure *square) {
    float deltaX = fabs(circle->center.x - fmax(square->center.x - square->sideLen / 2, fmin(circle->center.x, square->center.x + square->sideLen / 2)));
    float deltaY = fabs(circle->center.y - fmax(square->center.y - square->sideLen / 2, fmin(circle->center.y, square->center.y + square->sideLen / 2)));

    if (deltaX > circle->radius + square->sideLen / 2) return 0;
    if (deltaY > circle->radius + square->sideLen / 2) return 0;

    if (deltaX <= square->sideLen / 2) return 1;
    if (deltaY <= square->sideLen / 2) return 1;

    float cornerDistance = pow(deltaX - square->sideLen / 2, 2) + pow(deltaY - square->sideLen / 2, 2);
    return cornerDistance <= pow(circle->radius, 2);
}

int overlap(Figure *fig1, Figure *fig2) {
    if(fig1 == NULL || fig2 == NULL || fig1 == fig2)
        return 0;

    if(fig1->type == fig2->type) {
        if(fig1->type == CIRCLE)
            return circlesOverlap(fig1, fig2);

        return squaresOverlap(fig1, fig2);
    } else {
        if(fig1->type == CIRCLE)
            return circleAndSquareOverlap(fig1, fig2);

        return circleAndSquareOverlap(fig2, fig1);
    }

}

int isNodeInside(Node *child, Node *parent) {
    if(child == NULL || parent == NULL || child == parent)
        return 0;

    return child->box.min.x >= parent->box.min.x && child->box.max.x <= parent->box.max.x 
        && child->box.min.y >= parent->box.min.y && child->box.max.y <= parent->box.max.y;
}

int isNeighbor(Node *node1, Node *node2) {
    if(node1 == NULL || node2 == NULL || node1 == node2)
        return 0;

    return (node1->box.min.x == node2->box.max.x && !(node1->box.min.y > node2->box.max.y || node1->box.max.y < node2->box.min.y))
        || (node1->box.max.x == node2->box.min.x && !(node1->box.min.y > node2->box.max.y || node1->box.max.y < node2->box.min.y))
        || (node1->box.min.y == node2->box.max.y && !(node1->box.min.x > node2->box.max.x || node1->box.max.x < node2->box.min.x))
        || (node1->box.max.y == node2->box.min.y && !(node1->box.min.x > node2->box.max.x || node1->box.max.x < node2->box.min.x));
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

int main() {
    Figure *figures[19];
    figures[0] = createSquare(15.0, 505.0, 10);
    figures[1] = createSquare(580.0, 490.0, 20);
    figures[2] = createCircle(-267.0, -15.0, 20);
    figures[3] = createCircle(18.0, 20.0, 15);
    figures[4] = createSquare(-618.0, 456.0, 6);
    figures[5] = createSquare(-134.0, 80.0, 8);
    figures[6] = createCircle(-259.0, 5.0, 25);
    figures[7] = createSquare(34.0, 30.0, 9);
    figures[8] = createSquare(780.0, 7.0, 10);
    figures[9] = createSquare(-890.0, -120.0, 12);
    figures[10] = createSquare(-230.0, -745.0, 11);
    figures[11] = createSquare(115.0, -379.0, 13);
    figures[12] = createSquare(540.0, -637.0, 14);
    figures[13] = createSquare(13.0, 789.0, 16); 
    figures[14] = createSquare(456.0, 932.0, 15);
    figures[15] = createSquare(856.0, 764.0, 18);
    figures[16] = createSquare(8.0, 495.0, 16);
    figures[17] = createSquare(585.0, 485.0, 12);
    figures[18] = createSquare(582.0, 483.0, 8);

    Node *root = build_tree(figures, 19);
    printTree(root, 0);

    printOverlaps(root->children[0], root);
    printOverlaps(root->children[1]->children[3], root);
    printOverlaps(root->children[1]->children[2], root);
    printOverlaps(root->children[1]->children[1], root);

    freeTree(root);

    return 0;
}