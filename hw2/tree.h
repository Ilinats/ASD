#ifndef TREE_H
#define TREE_H

typedef struct inventory {
    char *name;
    int quantity;
    struct inventory *next;
} Inventory;

typedef struct node {
    char *npcLine;
    char **replies;
    int replies_count;
    char *requiredItem;
    int requiredItemQuantity;
    struct node **next;
    int next_count;
 } Node;

Node *init_node(char *npcLine, char **replies, int replies_count, Node **next, int next_count, char *requiredItem, int requiredItemQuantity);
Inventory *init_inventory(char *name, int quantity);
Inventory *add_inventory(Inventory *inventory, char *name, int quantity);
Inventory *use_inventory(Inventory *inventory, char *name, int quantity, int *flag);
void printInventory(Inventory *inventory);

#endif