#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct figure {
    float x;
    float y;
    char *name;
} Figure;

typedef struct square {
    Figure *center;
    int sideLen;
} Square;

typedef struct circle {
    Figure *center;
    int radius;
} Circle;

typedef struct figureList {
    void **figures;
    int figuresCount;
    char *types;
} figureList;

typedef struct node {
    float xMax, yMax, xMin, yMin;
    struct node **children;
    void **figures;
    char *types;
    int figuresCount;
    int reachedLimit;
} Node;

typedef struct pair {
    void *figure1;
    void *figure2;
} Pair;

typedef struct pairList {
    Pair **pairs;
    int pairsCount;
} pairList;

Figure *createFigure(float x, float y, const char *prefix, int *count) {
    Figure *figure = (Figure *)malloc(sizeof(Figure));
    figure->x = x;
    figure->y = y;
    figure->name = (char *)malloc(10);
    snprintf(figure->name, 10, "%s%d", prefix, ++(*count));

    return figure;
}

Circle *createCircle(Figure *center, int radius) {
    Circle *circle = (Circle *)malloc(sizeof(Circle));
    circle->center = center;
    circle->radius = radius;

    return circle;
}

Square *createSquare(Figure *center, int sideLen) {
    Square *square = (Square *)malloc(sizeof(Square));
    square->center = center;
    square->sideLen = sideLen;

    return square;
}

Node *createNode(float xMax, float yMax, float xMin, float yMin) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->xMax = xMax;
    node->yMax = yMax;
    node->xMin = xMin;
    node->yMin = yMin;
    node->figuresCount = 0;
    node->children = NULL;
    node->figures = NULL;
    node->types = NULL;
    node->reachedLimit = 0;

    return node;
}

void printTree(Node *node) {
    if(node == NULL)
        return;

    printf("Node: (%f, %f, %f, %f)\n", node->xMax, node->yMax, node->xMin, node->yMin);
    printf("Figures: ");
    for(int i = 0; i < node->figuresCount; i++) {
        if(node->types[i] == 's')
            printf("%s(%f, %f) ", ((Square*)node->figures[i])->center->name, ((Square *)node->figures[i])->center->x, ((Square *)node->figures[i])->center->y);
        else
            printf("%s(%f, %f) ", ((Circle*)node->figures[i])->center->name, ((Circle *)node->figures[i])->center->x, ((Circle *)node->figures[i])->center->y);
    }
    printf("\n\n");

    if(node->children != NULL) {
        for(int i = 0; i < 4; i++)
        printTree(node->children[i]);
    }
}

void allocateChildren(Node *node) {
    if(node->children != NULL)
        return;

    node->children = (Node **) malloc(sizeof(Node *) * 4);
    for (int i = 0; i < 4; i++)
        node->children[i] = NULL;

    return;
}

void insertFigure(Node *node, void *figure, char type) {
    if(node->figuresCount+1 < 10 && !node->reachedLimit) {
        if(node->figures == NULL) {
            node->figures = (void **) malloc(sizeof(void *) * 10);
            node->types = (char *) malloc(sizeof(char) * 10);
        } else {
            node->figures = (void **) realloc(node->figures, sizeof(void *) * (node->figuresCount + 1));
            node->types = (char *) realloc(node->types, sizeof(char) * (node->figuresCount + 1));
        }

        node->figures[node->figuresCount] = figure;
        node->types[node->figuresCount++] = type;

    } else {
        node->reachedLimit = 1;
        allocateChildren(node);

        for (int i = 0; i < 4; i++) {
            float xMid = (node->xMax + node->xMin) / 2;
            float yMid = (node->yMax + node->yMin) / 2;
            float child_x_min, child_x_max, child_y_min, child_y_max;
            switch (i) {
                case 0: // Top left
                    child_x_min = node->xMin;
                    child_x_max = xMid;
                    child_y_min = yMid;
                    child_y_max = node->yMax;
                    break;
                case 1: // Top right
                    child_x_min = xMid;
                    child_x_max = node->xMax;
                    child_y_min = yMid;
                    child_y_max = node->yMax;
                    break;
                case 2: // Bottom left
                    child_x_min = node->xMin;
                    child_x_max = xMid;
                    child_y_min = node->yMin;
                    child_y_max = yMid;
                    break;
                case 3: // Bottom right
                    child_x_min = xMid;
                    child_x_max = node->xMax;
                    child_y_min = node->yMin;
                    child_y_max = yMid;
                    break;
            }

            for(int j = 0; j < node->figuresCount; j++) {
                if(node->figures[j] == NULL)
                    continue;
    
                if(node->types[j] == 's') {
                    Square *square = (Square *)node->figures[j];
                    if(square->center->x >= child_x_min && square->center->x <= child_x_max &&
                        square->center->y >= child_y_min && square->center->y <= child_y_max) {
                        if(node->children[i] == NULL)
                            node->children[i] = createNode(child_x_max, child_y_max, child_x_min, child_y_min);

                        insertFigure(node->children[i], node->figures[j], node->types[j]);
                        printf("Inserted %s\n", square->center->name);
                        node->figures[j] = NULL;
                    }
                }
                else {
                    Circle *circle = (Circle *)node->figures[j];
                    if(circle->center->x >= child_x_min && circle->center->x <= child_x_max &&
                        circle->center->y >= child_y_min && circle->center->y <= child_y_max) {
                        if(node->children[i] == NULL)
                            node->children[i] = createNode(child_x_max, child_y_max, child_x_min, child_y_min);

                        insertFigure(node->children[i], node->figures[j], node->types[j]);
                        printf("Inserted %s\n", circle->center->name);
                        node->figures[j] = NULL;
                    }
                }
            }

            if(type == 's') {
                Square *square = (Square *)figure;
                if(square->center->x >= child_x_min && square->center->x <= child_x_max &&
                    square->center->y >= child_y_min && square->center->y <= child_y_max) {
                    if(node->children[i] == NULL)
                        node->children[i] = createNode(child_x_max, child_y_max, child_x_min, child_y_min);

                    insertFigure(node->children[i], figure, type);
                    printf("Inserted new %s\n", square->center->name);
                }
            }
            else {
                Circle *circle = (Circle *)figure;
                if(circle->center->x >= child_x_min && circle->center->x <= child_x_max &&
                    circle->center->y >= child_y_min && circle->center->y <= child_y_max) {
                    if(node->children[i] == NULL)
                        node->children[i] = createNode(child_x_max, child_y_max, child_x_min, child_y_min);

                    insertFigure(node->children[i], figure, type);
                }
            }
        }

        node->figuresCount = 0;
        node->figures = NULL;
    }

    return;
}

Node *build_tree(figureList *figures) {
    Node *root = createNode(1000, 1000, -1000, -1000);

    for (int i = 0; i < figures->figuresCount; i++)
        insertFigure(root, figures->figures[i], figures->types[i]);

    return root;
}

int areNeighbors(Node *node1, Node *node2) {
    if (node1 == NULL || node2 == NULL)
        return 0;

    return (
        ((node1->xMin == node2->xMax || node1->xMax == node2->xMin) &&
         (node1->yMax >= node2->yMin && node1->yMin <= node2->yMax)) ||

        ((node1->yMin == node2->yMax || node1->yMax == node2->yMin) &&
         (node1->xMax >= node2->xMin && node1->xMin <= node2->xMax)) ||

        ((node1->xMin == node2->xMax && node1->yMax == node2->yMin) ||
         (node1->xMax == node2->xMin && node1->yMax == node2->yMin) ||
         (node1->xMin == node2->xMax && node1->yMin == node2->yMax) ||
         (node1->xMax == node2->xMin && node1->yMin == node2->yMax))
    );
}

Node *findGrandparent(Node *root, Node *child) {
    if (root == NULL || child == NULL)
        return NULL;

    for (int i = 0; i < 4; i++) {
        if(root->children != NULL) {
            Node *parent = root->children[i];
            if (parent != NULL && parent->children != NULL) {
                for (int j = 0; j < 4; j++) {
                    if (parent->children[j] == child)
                        return root;
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        if(root->children != NULL) {
            Node *grandparent = findGrandparent(root->children[i], child);
            if (grandparent != NULL)
                return grandparent;
        }
    }

    return NULL;
}

Node *findParent(Node *root, Node *child) {
    if (root == NULL || child == NULL)
        return NULL;

    for (int i = 0; i < 4; i++) {
        if (root->children != NULL && root->children[i] == child)
            return root;
    }

    for (int i = 0; i < 4; i++) {
        Node *parent;

        if(root->children != NULL)
            parent = findParent(root->children[i], child);

        if (parent != NULL)
            return parent;
    }

    return NULL;
}

int areCirclesOverlapped(Circle *circle1, Circle *circle2) {
    float distance = sqrt(pow(circle1->center->x - circle2->center->x, 2) + pow(circle1->center->y - circle2->center->y, 2));
    return distance <= circle1->radius + circle2->radius;
}

int areSquaresOverlapped(Square *square1, Square *square2) {
    float x1 = square1->center->x - square1->sideLen / 2;
    float x2 = square1->center->x + square1->sideLen / 2;
    float y1 = square1->center->y - square1->sideLen / 2;
    float y2 = square1->center->y + square1->sideLen / 2;

    float x3 = square2->center->x - square2->sideLen / 2;
    float x4 = square2->center->x + square2->sideLen / 2;
    float y3 = square2->center->y - square2->sideLen / 2;
    float y4 = square2->center->y + square2->sideLen / 2;

    return (x1 <= x4 && x2 >= x3 && y1 <= y4 && y2 >= y3);
}

int areSquareAndCircleOverlapped(Square *square, Circle *circle) {
    float deltaX = fabs(circle->center->x - fmax(square->center->x - square->sideLen / 2, fmin(circle->center->x, square->center->x + square->sideLen / 2)));
    float deltaY = fabs(circle->center->y - fmax(square->center->y - square->sideLen / 2, fmin(circle->center->y, square->center->y + square->sideLen / 2)));

    if (deltaX > circle->radius + square->sideLen / 2) return 0;
    if (deltaY > circle->radius + square->sideLen / 2) return 0;

    if (deltaX <= square->sideLen / 2) return 1;
    if (deltaY <= square->sideLen / 2) return 1;

    float cornerDistance = pow(deltaX - square->sideLen / 2, 2) + pow(deltaY - square->sideLen / 2, 2);
    return cornerDistance <= pow(circle->radius, 2);
}

int areOverlapped(void *fig1, void *fig2, char type1, char type2) {
    if (fig1 == NULL || fig2 == NULL)
        return 0;

    int isCircle1 = type1 == 'c';
    int isCircle2 = type2 == 'c';

    if (isCircle1 && isCircle2)
        return areCirclesOverlapped((Circle *)fig1, (Circle *)fig2);
    else if ((isCircle1 && !isCircle2) || (!isCircle1 && isCircle2)) 
        return areSquareAndCircleOverlapped(
            isCircle1 ? (Square *)fig2 : (Square *)fig1,
            isCircle1 ? (Circle *)fig1 : (Circle *)fig2
        );
    else
        return areSquaresOverlapped((Square *)fig1, (Square *)fig2);
}

void addToPairList(pairList *pairs, void *figure1, void *figure2) {
    if (figure1 != NULL && figure2 != NULL) {
        if (pairs->pairs == NULL)
            pairs->pairs = (Pair **)malloc(sizeof(Pair *) * 10);
        else
            pairs->pairs = (Pair **)realloc(pairs->pairs, sizeof(Pair *) * (pairs->pairsCount + 1));

        pairs->pairs[pairs->pairsCount] = (Pair *)malloc(sizeof(Pair));
        pairs->pairs[pairs->pairsCount]->figure1 = figure1;
        pairs->pairs[pairs->pairsCount]->figure2 = figure2;
        pairs->pairsCount++;
    }
}

pairList *findOverlaps(Node *node, Node *root) {
    pairList *pairs = (pairList *) malloc(sizeof(pairList));
    pairs->pairsCount = 0;
    pairs->pairs = NULL;

    Node *grandparent = findGrandparent(root, node);
    Node *parent = findParent(root, node);

    for(int i = 0; i < 4; i++) {
        if(parent->children[i] != NULL && parent->children[i] != node) {
            for(int j = 0; j < parent->children[i]->figuresCount; j++) {
                for(int k = 0; k < node->figuresCount; k++) {
                    if (parent->types != NULL && node->types != NULL &&
                        parent->types[j] && node->types[k] &&
                        areOverlapped(parent->children[i]->figures[j], node->figures[k], parent->types[j], node->types[k])) {
                        addToPairList(pairs, parent->children[i]->figures[j], node->figures[k]);
                    }
                }
            }
        }
    }

    for(int i = 0; i < 4; i++) {
        if(grandparent != NULL && grandparent->children[i] != parent && areNeighbors(grandparent->children[i], node)) {
            for(int j = 0; j < grandparent->children[i]->figuresCount; j++) {
                for(int k = 0; k < node->figuresCount; k++) {
                    if (grandparent->types != NULL && node->types != NULL &&
                        grandparent->types[j] && node->types[k] &&
                        areOverlapped(grandparent->children[i]->figures[j], node->figures[k], grandparent->types[j], node->types[k])) {
                        addToPairList(pairs, grandparent->children[i]->figures[j], node->figures[k]);
                    }
                }
            }
        }
    }

    for(int i = 0; i < node->figuresCount; i++) {
        for(int j = i + 1; j < node->figuresCount; j++) {
            if(areOverlapped(node->figures[i], node->figures[j], node->types[i], node->types[j]))
                addToPairList(pairs, node->figures[i], node->figures[j]);
        }
    }

    return pairs;
}

void printPairs(pairList *pairs) {
    for(int i = 0; i < pairs->pairsCount; i++) {
        if(pairs->pairs[i]->figure1 != NULL && pairs->pairs[i]->figure2 != NULL) {
            if(pairs->pairs[i]->figure1 != NULL && pairs->pairs[i]->figure2 != NULL) {
                if(((Square *)pairs->pairs[i]->figure1)->center->x < ((Square *)pairs->pairs[i]->figure2)->center->x)
                    printf("%d) %s %s\n", i+1, ((Square *)pairs->pairs[i]->figure1)->center->name, ((Square *)pairs->pairs[i]->figure2)->center->name);
                else
                    printf("%d) %s %s\n", i+1, ((Square *)pairs->pairs[i]->figure2)->center->name, ((Square *)pairs->pairs[i]->figure1)->center->name);
            }
        }
    }
    printf("\n");
}

void printOverlaps(Node *node, Node *root) {
    pairList *overlaps = findOverlaps(node, root);
    if(overlaps->pairsCount == 0)
        printf("No overlaps found.\n");
    else
        printPairs(overlaps);
}

int main() {

    int squareCount = 0;
    int circleCount = 0;

    figureList *figuresList = (figureList *)malloc(sizeof(figureList));
    figuresList->figures = (void **)malloc(sizeof(void *) * 19);
    figuresList->types = (char *)malloc(sizeof(char ) * 19);
    figuresList->figures[0] = (void *)createSquare(createFigure(15.0, 505.0, "sqr", &squareCount), 10);
    figuresList->types[0] = 's';
    figuresList->figures[1] = (void *)createSquare(createFigure(580.0, 490.0, "sqr", &squareCount), 20);
    figuresList->types[1] = 's';
    figuresList->figures[2] = (void *)createCircle(createFigure(-267.0, -15.0, "cir", &circleCount), 20);
    figuresList->types[2] = 'c';
    figuresList->figures[3] = (void *)createCircle(createFigure(18.0, 20.0, "cir", &circleCount), 15);
    figuresList->types[3] = 'c';
    figuresList->figures[4] = (void *)createSquare(createFigure(-618.0, 456.0, "sqr", &squareCount), 6); //3
    figuresList->types[4] = 's';
    figuresList->figures[5] = (void *)createSquare(createFigure(-134.0, 80.0, "sqr", &squareCount), 8); //4
    figuresList->types[5] = 's';
    figuresList->figures[6] = (void *)createCircle(createFigure(-259.0, 5.0, "cir", &circleCount), 25); //3 circle
    figuresList->types[6] = 'c';
    figuresList->figures[7] = (void *)createSquare(createFigure(34.0, 30.0, "sqr", &squareCount), 9); // 5
    figuresList->types[7] = 's';
    figuresList->figures[8] = (void *)createSquare(createFigure(780.0, 7.0, "sqr", &squareCount), 10); // 6
    figuresList->types[8] = 's';
    figuresList->figures[9] = (void *)createSquare(createFigure(-890.0, -120.0, "sqr", &squareCount), 12); // 7
    figuresList->types[9] = 's';
    figuresList->figures[10] = (void *)createSquare(createFigure(-230.0, -745.0, "sqr", &squareCount), 11); // 8
    figuresList->types[10] = 's';
    figuresList->figures[11] = (void *)createSquare(createFigure(115.0, -379.0, "sqr", &squareCount), 13); // 9
    figuresList->types[11] = 's';
    figuresList->figures[12] = (void *)createSquare(createFigure(540.0, -637.0, "sqr", &squareCount), 14); // 10
    figuresList->types[12] = 's';
    figuresList->figures[13] = (void *)createSquare(createFigure(13.0, 789.0, "sqr", &squareCount), 16); 
    figuresList->types[13] = 's';
    figuresList->figures[14] = (void *)createSquare(createFigure(456.0, 932.0, "sqr", &squareCount), 15); //12
    figuresList->types[14] = 's';
    figuresList->figures[15] = (void *)createSquare(createFigure(856.0, 764.0, "sqr", &squareCount), 18);
    figuresList->types[15] = 's';
    figuresList->figures[16] = (void *)createSquare(createFigure(8.0, 495.0, "sqr", &squareCount), 16); //14
    figuresList->types[16] = 's';
    figuresList->figures[17] = (void *)createSquare(createFigure(585.0, 485.0, "sqr", &squareCount), 12); //15
    figuresList->types[17] = 's';
    figuresList->figures[18] = (void *)createSquare(createFigure(582.0, 483.0, "sqr", &squareCount), 8); //16
    figuresList->types[18] = 's';
    figuresList->figuresCount = 19;

    Node *root = build_tree(figuresList);
    printTree(root);

    printOverlaps(root->children[0], root);
    printOverlaps(root->children[1]->children[3], root);
    printOverlaps(root->children[1]->children[2], root);
    printOverlaps(root->children[1]->children[1], root);

    return 0;
}