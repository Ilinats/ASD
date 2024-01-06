#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node *init_node(char *npcLine, char **replies, int replies_count, Node **next, int next_count, char *requiredItem, int requiredItemQuantity) {
    Node *node = (Node *)malloc(sizeof(Node));

    node->npcLine = npcLine;
    node->replies = replies;
    node->replies_count = replies_count;
    node->next = next;
    node->next_count = next_count;
    node->requiredItem = requiredItem;
    node->requiredItemQuantity = requiredItemQuantity;

    return node;
}