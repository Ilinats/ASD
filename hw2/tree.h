#ifndef TREE_H
#define TREE_H

#define MAX_LEN 500

typedef struct node {
    char npcLine[MAX_LEN];
    char **replies;
    struct node **next;
} Node;

Node *init_node(char *line, char **playerReplies, Node **nextNode);

#endif