/* Условия:
1. Root-ът е черен
2. Наследниците на червените трябва да са черни
3. Листата (NULL) са черни
4. Всеки един път от корена надолу ще съдържат еднакъв брой черни node-ове */

#include <stdio.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int val;
} Node;

Node *create_node(int val) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->val = val;
    node->parent == NULL;

    return node;
}

Node *insertNode(Node *tree, int val)
{
    if (tree == NULL)
        return create_node(val);

    if (val < tree->val) {
        tree->left = insertNode(tree->left, val);
        tree->left->parent = tree;
    }
    else if (val > tree->val) {
        tree->right = insertNode(tree->right, val);
        tree->right->parent = tree;
    }

    return tree;
}

void insert(Node *root, int val) {
    Node *newNode = create_node(val);
    Node *current = root;

    if(current == NULL) {
        root = newNode;
        return;
    }

    while(1) {
        if(current->val > val) {
            if(current->left == NULL)
                break;
            
            current = current->left;
        } else {
            if(current->right == NULL)
                break;
            
            current = current->right;
        }
    }

    if(current->val > val)
        current->left = newNode;
    else
        current->right = newNode;

    newNode->parent = current;
}

Node *rightRotation(Node* tree) {
    
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

Node *leftRotation(Node *tree) {
    Node *rightTree = tree->right;
    Node *rightLeftTree = rightTree->left;
    Node *parent = tree->parent;

    rightTree->left = tree;
    tree->right = rightLeftTree;

    tree->parent = rightTree;
    rightTree->parent = parent;
    rightLeftTree->parent = tree;

    return rightTree;
}

void print(Node *tree) {
    if(tree == NULL)
        return;

    print(tree->left);
    printf("%d ", tree->val);
    print(tree->right);
}

int main() {
    Node *tree = create_node(9);
    insertNode(tree, 15);
    insertNode(tree, 7);
    insertNode(tree, 13);
    insertNode(tree, 11);
    insertNode(tree, 6);
    insertNode(tree, 8);
    insertNode(tree, 17);
}