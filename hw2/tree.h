#ifndef TREE_H
#define TREE_H

#include "linkedList.h"

#define MAX_LEN 500
#define MAX_REPLIES 6

typedef struct node {
    char npcLine[MAX_LEN];
    char **replies;
    List *next;
} Node;

Node init_node(char *line, char **playerReplies, List *nextNode);

#endif