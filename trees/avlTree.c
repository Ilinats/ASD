#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    int val;
    int height;
} Node;

Node *create_node(int val) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->val = val;
    node->height = 1;

    return node;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *tree) {
    if(tree == NULL)
        return 0;

    return tree->height;
}

int balanceFactor(Node *tree) {
    return height(tree->left) - height(tree->right);
}

Node *leftRotation(Node *tree) {
    Node *leftTree = tree->left;
    Node *leftRightTree = leftTree->right;

    leftTree->right = tree;
    tree->left = leftRightTree;

    leftTree->height = 1 + max(height(leftTree->left), height(leftTree->right));
    tree->height = 1 + max(height(tree->left), height(tree->right));

    return leftTree;
}

Node *rightRotation(Node *tree) {
    Node *rightTree = tree->right;
    Node *rightLeftTree = rightTree->left;

    rightTree->left = tree;
    tree->right = rightLeftTree;

    rightTree->height = 1 + max(height(rightTree->left), height(rightTree->right));
    tree->height = 1 + max(height(tree->left), height(tree->right));

    return rightTree;
}

Node *insertNode(Node *root, int val)
{
    if (root == NULL)
        return create_node(val);

    if (val < root->val)
        root->left = insertNode(root->left, val);

    else if (val > root->val)
        root->right = insertNode(root->right, val);

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = balanceFactor(root);
    
    if(balance < -1) {
        if(val > root->right->val)
            return leftRotation(root);

        root->right = rightRotation(root->right);
        return leftRotation(root);

    } else if(balance > 1) {
        if(val < root->left->val)
            return rightRotation(root);

        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    
    return root;
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

void print(Node *tree) {
    if(tree == NULL) {
        return;
    }

    print(tree->left);
    printf("%d ", tree->val);
    print(tree->right);
}

void printTree2(Node *root)
{
    if (root == NULL)
        return;

    printf("Value: %d, Height: %d \n", root->val, root->height);
    printTree2(root->left);
    printTree2(root->right);
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
    printTree2(tree);

    return 0;
}