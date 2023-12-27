#ifndef TREE_H
#define TREE_H

#include "linkedList.h"

#define MAX_LEN 500
#define MAX_REPLIES 6

typedef struct node {
    char npcLine[MAX_LEN];
    List *replies;
    List *next;
} Node;

Node init_node(char *line, List *playerReplies, List *nextNode);

#endif