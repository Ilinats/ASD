#include <stdlib.h>
#include "figure.h"
#include <math.h>
#include <stdio.h>

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