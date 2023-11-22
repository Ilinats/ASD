#include <stdio.h>
#include <stdlib.h>
//#include <../vectors/vector.c>

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

Node *deleteNode(Node *tree, int val) {
    if(tree == NULL)
        return NULL;

    if(tree->val == val) {
        if(tree->left == NULL){
            Node *temp = tree;
            tree = tree->right;
            free(temp);
        } else if(tree->right == NULL) {
            Node *temp = tree;
            tree = tree->left;
            free(temp);
        } else {
            Node *rightTree = tree->right;

            while(rightTree->left != NULL)
                rightTree = rightTree->left;

            tree->val = rightTree->val;
            tree->right = deleteNode(tree->right, rightTree->val);
        }

        return tree;

    } else if(tree->val > val)  
        tree->left = deleteNode(tree->left, val);
    else if(tree->val < val)
        tree->right = deleteNode(tree->right, val);

    return tree;
}



int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *tree) {
    if(tree == NULL)
        return 0;

    return 1 + max(height(tree->left), height(tree->right));
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
    deleteNode(tree, 5);
    printf("\n");
    print(tree);

    return 0;
}