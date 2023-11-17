#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    int val;
} Node;

Node *create_node(int val) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->val = val;

    return node;
}

void insertNode(Node *tree, int val) {
    if(tree == NULL) {
        tree = create_node(val);
        return;
    }

    if(tree->val > val) {
        if(tree->left == NULL) {
            Node *newNode = create_node(val);
            tree->left = newNode;
            return;
        }
            
        insertNode(tree->left, val);

    } else if(tree->val < val) {
        if(tree->right == NULL) {
            Node *newNode = create_node(val);
            tree->right = newNode;
            return;
        } else
            insertNode(tree->right, val);
    }
}

void deleteNode(Node *tree, int val) {
    if(tree->val == val) {
        tree = NULL;
        
    }
}

void print(Node *tree) {
    if(tree == NULL) {
        return;
    }

    print(tree->left);
    printf("%d ", tree->val);
    print(tree->right);
}
int main() {
    Node *tree = create_node(5);
    insertNode(tree, 3);
    insertNode(tree, 7);
    insertNode(tree, 2);
    insertNode(tree, 4);
    insertNode(tree, 6);
    insertNode(tree, 8);

    print(tree);

    return 0;
}