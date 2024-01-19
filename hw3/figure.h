#ifndef FIGURE_H
#define FIGURE_H

typedef struct center {
    float x;
    float y;
} Center;

typedef struct Figure {
    Center center;
    char *name;
    int sideLen;
    int radius;
} Figure;

Figure *createFigure(Center *center, char *name, int sideLen, int radius);
int areOverlaped(Figure fig1, Figure fig2);

#endif