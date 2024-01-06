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

Inventory *init_inventory(char *name, int quantity) {
    Inventory *inventory = (Inventory *)malloc(sizeof(Inventory));

    inventory->name = name;
    inventory->quantity = quantity;
    inventory->next = NULL;

    return inventory;
}

Inventory *add_inventory(Inventory *inventory, char *name, int quantity) {
    Inventory *temp = inventory;
    if (temp == NULL) {
        inventory = init_inventory(strdup(name), quantity);
        return inventory;
    }

    do {
        if (strcmp(temp->name, name) == 0) {
            temp->quantity += quantity;
            return inventory;
        }

        temp = temp->next;
    } while (temp != NULL);

    temp = init_inventory(name, quantity);
    temp->next = inventory;
    inventory = temp;

    return inventory;
}

Inventory *use_inventory(Inventory *inventory, char *name, int quantity, int *flag) {
    if(!inventory)
        return NULL;

    Inventory *temp = inventory;
    Inventory *prev = NULL;

    while(temp) {
        if(strcmp(temp->name, name) == 0 && temp->quantity >= quantity) {
            printf("You used %s from your inventory!\n\n", name);
            *flag = 1;
            temp->quantity -= quantity;
            
            if(temp->quantity < 1) {
                if(prev)
                    prev->next = temp->next;
                else
                    inventory = temp->next;

                free(temp);
                return inventory;
            }
        }
        prev = temp;
        temp = temp->next;
    }

    printf("You don't have the required item (or enoght of it) %s in your inventory!\n\n", name);
    return inventory;
}