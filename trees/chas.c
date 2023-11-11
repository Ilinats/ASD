/*  
    Dyrwaetata imat node-ve (wyrhowe), koito se razklonqwat. Purwiqt node e koren, a poslenite nadolu - lista.
    Ima znachenie ot koq strana na naslednicite. 
    Za da e durvo ne trqbwa da ima zatoworeni krugove, w koito da mojem da zabiem.
    Wisochina - ot korena do naj-niskoto listo. (korenut e niwo 0)
*/

#include <stdio.h>

typedef struct Node {
    Node *left;
    Node *right;
    int val;
} Node;

typedef struct BTree {
    Node *root;
} BTree;

Node *createNode(int val) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->val = val;
    return newNode;
}

BTree *init_tree() {
    BTree *tree = (BTree*)malloc(sizeof(BTree));
    tree->root = NULL;
    return tree;
}

void push(Node* tree, int val) {
    if(tree == NULL) {
        tree = newNode;
        return;
    }

    if(tree->val > val) {
        if(tree->left == NULL) {
            Node *newNode = createNode(val);
            tree->left = newNode;
            return;
        }
        push(tree->left, val);
    } else {
        if(tree->right == NULL) {
            Node *newNode = createNode(val);
            tree->right = newNode;
            return;
        }
        push(tree->right, val);
    }
} 

void printTree(Node *tree) {
    if(tree == NULL) {
        return;
    }
    printTree(tree->left);
    printf("%d ", tree->val);
    printTree(tree->right);
}

int main() {

    return 0;
}