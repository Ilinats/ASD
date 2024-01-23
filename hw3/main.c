#include <stdio.h>
#include <stdlib.h>
#include "quadTree.h"
#include "figure.h"

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