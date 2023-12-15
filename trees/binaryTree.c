#include <stdio.h>
#include <stdlib.h>

/*AVL дърво: Максималната височина за 12 върха е 5. 
Връзка между височината и минималният брой върхове: T(h+1) = T(h) + T(h-1) + 1 ~ 1.44logn ~ O(logn)
Времето за търсене за 2^n дърво: O(log2^n) = O(n)
А за n*2^n = O(logn + n) = O(n)*/

typedef struct tree {
    int value;
    struct tree* left;
    struct tree* right;
} tree;

void flattenTree2(tree* root) {
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

tree *flatten(tree *root) {

    if (root == NULL)
        return NULL;

    if (root->left == NULL && root->right == NULL)
        return root;

    if (root->left == NULL)
        return flatten(root->right);
        
    if (root->right == NULL) {
        root->right = root->left;
        return flatten(root->right);
    }

    tree *leftEnd = flatten(root->left);
    tree *rightEnd = flatten(root->right);

    leftEnd->right = root->right;
    root->right = root->left;
    root->left = NULL;

    return rightEnd;
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

    flatten(root);
    printf("Flattened tree: ");
    printPreorder(root);

    return 0;
}
