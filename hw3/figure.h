#ifndef FIGURE_H
#define FIGURE_H

typedef struct figure {
    float x;
    float y;
    char *name;
} Figure;

typedef struct square {
    Figure center;
    float sideLen;
} Square;

typedef struct circle {
    Figure center;
    float radius;
} Circle;

Square *createSquare(Figure coordinates, float len);
Circle *createCircle(Figure coordinates, float r);
int squareOverlap(Square sq1, Square sq2);
int circleOverlap(Circle c1, Circle s2);
int areOverlaped(Square sq, Circle c);

#endif