#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int value;
    struct tree* left;
    struct tree* right;
} tree;

void flattenTree(tree* root) {
    while (root != NULL) {
        if (root->left != NULL) {
            tree* temp = root->left;
            
            while (temp->right != NULL)
                temp = temp->right;

            temp->right = root->right;

            root->right = root->left;
            root->left = NULL;
        }

        root = root->right;
    }
}

tree* createNode(int value) {
    tree* newNode = (tree*)malloc(sizeof(tree));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void printPreorder(tree* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

int main() {

    tree* root = createNode(1);
    root->left = createNode(2);
    root->left->left = createNode(3);
    root->left->right = createNode(4);
    root->right = createNode(5);
    root->right->right = createNode(6);

    flattenTree(root);
    printf("Flattened tree: ");
    printPreorder(root);

    return 0;
}
