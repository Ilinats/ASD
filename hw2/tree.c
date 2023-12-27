#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node *init_node(char *line, char *playerReplies[], Node **nextNode) {
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->npcLine, line);
    
    for(int i = 0; playerReplies[i] != NULL; i++) {
        strcpy(node->replies[i], playerReplies[i]);
        node->next[i] = nextNode[i];
    }

    return node;
}