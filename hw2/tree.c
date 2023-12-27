#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node init_node(char *line, List *playerReplies, List *nextNode) {
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->npcLine, line);
    node->replies = playerReplies;
    node->next = nextNode;

    return node;
}