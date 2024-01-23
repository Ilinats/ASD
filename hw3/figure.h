#ifndef FIGURE_H
#define FIGURE_H

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

Circle *createCircle(float x, float y, int radius);
Square *createSquare(float x, float y, int sideLen);
int circlesOverlap(Circle *fig1, Circle *fig2);
int squaresOverlap(Square *fig1, Square *fig2);
int circleAndSquareOverlap(Circle *circle, Square *square);
int overlap(Figure *fig1, Figure *fig2);

#endif