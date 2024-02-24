#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef enum{
    CIRCLE,
    SQUARE
} FigureType;

typedef struct {
    float x;
    float y;
    char *name;
    FigureType type;
} Figure;

typedef struct {
    Figure base;
    int sideLen;
} Square;

typedef struct {
    Figure base;
    int radius;
} Circle;

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

Circle *createCircle(float x, float y, int radius) {
    static int count = 0;

    Circle *circle = (Circle *) malloc(sizeof(Circle));
    circle->base.x = x;
    circle->base.y = y;
    circle->radius = radius;
    circle->base.type = CIRCLE;

    circle->base.name = (char *)malloc(10);
    snprintf(circle->base.name, 10, "%s%d", "circ", ++count);

    return circle;
}

Square *createSquare(float x, float y, int sideLen) {
    static int count = 0;

    Square *square = (Square *) malloc(sizeof(Square));
    square->base.x = x;
    square->base.y = y;
    square->sideLen = sideLen;
    square->base.type = SQUARE;

    square->base.name = (char *)malloc(10);
    snprintf(square->base.name, 10, "%s%d", "sqr", ++count);

    return square;
}

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

int circlesOverlap(Circle *fig1, Circle *fig2) {
    float distance = sqrt(pow(fig1->base.x - fig2->base.x, 2) + pow(fig1->base.y - fig2->base.y, 2));
    return distance <= fig1->radius + fig2->radius;
}

int squaresOverlap(Square *fig1, Square *fig2) {
    float x1 = fig1->base.x - fig1->sideLen / 2;
    float x2 = fig1->base.x + fig1->sideLen / 2;
    float y1 = fig1->base.y - fig1->sideLen / 2;
    float y2 = fig1->base.y + fig1->sideLen / 2;

    float x3 = fig2->base.x - fig2->sideLen / 2;
    float x4 = fig2->base.x + fig2->sideLen / 2;
    float y3 = fig2->base.y - fig2->sideLen / 2;
    float y4 = fig2->base.y + fig2->sideLen / 2;

    return !(x2 < x3 || x4 < x1 || y2 < y3 || y4 < y1);
}

int circleAndSquareOverlap(Circle *circle, Square *square) {
    float deltaX = fabs(circle->base.x - fmax(square->base.x - square->sideLen / 2, fmin(circle->base.x, square->base.x + square->sideLen / 2)));
    float deltaY = fabs(circle->base.y - fmax(square->base.y - square->sideLen / 2, fmin(circle->base.y, square->base.y + square->sideLen / 2)));

    if (deltaX > circle->radius + square->sideLen / 2) 
        return 0;
    if (deltaY > circle->radius + square->sideLen / 2) 
        return 0;

    if (deltaX <= square->sideLen / 2) 
        return 1;
    if (deltaY <= square->sideLen / 2) 
        return 1;

    float cornerDistance = pow(deltaX - square->sideLen / 2, 2) + pow(deltaY - square->sideLen / 2, 2);

    return cornerDistance <= pow(circle->radius, 2);
}

int overlap(Figure *fig1, Figure *fig2) {
    if(fig1 == NULL || fig2 == NULL || fig1 == fig2)
        return 0;

    if(fig1->type == fig2->type) {
        if(fig1->type == CIRCLE)
            return circlesOverlap((Circle* )fig1, (Circle* )fig2);

        return squaresOverlap((Square* )fig1, (Square* )fig2);
    } else {
        if(fig1->type == CIRCLE)
            return circleAndSquareOverlap((Circle* )fig1, (Square* )fig2);

        return circleAndSquareOverlap((Circle* )fig2, (Square* )fig1);
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

int main() {
    Figure *figures[19];
    figures[0] = (Figure* )createSquare(15.0, 505.0, 10);
    figures[1] = (Figure* )createSquare(580.0, 490.0, 20);
    figures[2] = (Figure* )createCircle(-267.0, -15.0, 20);
    figures[3] = (Figure* )createCircle(18.0, 20.0, 15);
    figures[4] = (Figure* )createSquare(-618.0, 456.0, 6);
    figures[5] = (Figure* )createSquare(-134.0, 80.0, 8);
    figures[6] = (Figure* )createCircle(-259.0, 5.0, 25);
    figures[7] = (Figure* )createSquare(34.0, 30.0, 9);
    figures[8] = (Figure* )createSquare(780.0, 7.0, 10);
    figures[9] = (Figure* )createSquare(-890.0, -120.0, 12);
    figures[10] = (Figure* )createSquare(-230.0, -745.0, 11);
    figures[11] = (Figure* )createSquare(115.0, -379.0, 13);
    figures[12] = (Figure* )createSquare(540.0, -637.0, 14);
    figures[13] = (Figure* )createSquare(13.0, 789.0, 16); 
    figures[14] = (Figure* )createSquare(456.0, 932.0, 15);
    figures[15] = (Figure* )createSquare(856.0, 764.0, 18);
    figures[16] = (Figure* )createSquare(8.0, 495.0, 16);
    figures[17] = (Figure* )createSquare(585.0, 485.0, 12);
    figures[18] = (Figure* )createSquare(582.0, 483.0, 8);

    Node *root = build_tree(figures, 19);
    printTree(root, 0);

    printOverlaps(root->children[0], root);
    printOverlaps(root->children[1]->children[3], root);
    printOverlaps(root->children[1]->children[2], root);
    printOverlaps(root->children[1]->children[1], root);

    freeTree(root);

    return 0;
}