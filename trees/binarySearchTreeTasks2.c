#include <stdio.h>
#include <stdlib.h>
#include "../vectors/vector.c"

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

void print(Node *tree) {
    if(tree == NULL)
        return;

    print(tree->left);
    printf("%d ", tree->val);
    print(tree->right);
}

int sumInInterval(Node* tree, int* arr, int* sum) {
    if(tree == NULL)
        return 0;

    if(tree->val >= arr[0] && tree->val <= arr[1])
        (*sum) += tree->val;

    sumInInterval(tree->right, arr, sum);
    sumInInterval(tree->left, arr, sum);

    return *sum;
}

void bstToGst(Node* tree, int* sum) {
    if(tree == NULL)
        return;
        
    if(tree->right != NULL)
        bstToGst(tree->right, sum);

    (*sum) += tree->val;
    tree->val = *sum - tree->val;
    bstToGst(tree->left, sum);

    return;
}

int isHeap(Node* tree) {
    if(tree == NULL)
        return 1;

    if(tree->left != NULL && tree->left->val > tree->val)
        return 0;

    if(tree->right != NULL && tree->right->val > tree->val)
        return 0;

    if(!(isHeap(tree->left) && isHeap(tree->right)))
        return 0;

    return 1;
}

Node* getNodeByVal(Node* tree, int val) {
    if(tree == NULL)
        return NULL;

    if(tree->val == val) 
        return tree;

    Node* leftResult = getNodeByVal(tree->left, val);

    if(leftResult != NULL)
        return leftResult;

    Node* rightResult = getNodeByVal(tree->right, val);
    return rightResult;
}

Node* findMax(Node* tree) {
    if(tree->right == NULL)
        return tree;

    findMax(tree->right);
}

Node* predecessor(Node* tree) {
    if (tree->left != NULL)
        return findMax(tree->left);

    Node* parent = tree->parent;
    while (parent != NULL && tree == parent->left) {
        tree = parent;
        parent = parent->parent;
    }
    
    return parent;
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

    Node *tree2 = create_node(9);
    insertNode(tree2, 15);
    insertNode(tree2, 7);
    insertNode(tree2, 13);
    insertNode(tree2, 11);
    insertNode(tree2, 6);
    insertNode(tree2, 8);
    insertNode(tree2, 17);

    Node *tree3 = create_node(100);
    tree3->left = create_node(19);
    tree3->right = create_node(36);
    tree3->left->left = create_node(17);
    tree3->left->right = create_node(3);
    tree3->right->right = create_node(1);

    int arr[2] = {11, 17};
    int sum = 0;
    printf("%d\n", sumInInterval(tree, arr, &sum));

    sum = 0;
    bstToGst(tree2, &sum);
    print(tree);
    printf("\n");
    print(tree2);
    printf("\nIs heap?: %s", isHeap(tree) ? "Yes" : "No");
    printf("\nIs heap?: %s\n", isHeap(tree3) ? "Yes" : "No");

    Node* temp = getNodeByVal(tree, 9);
    //Node* successor = successor(temp);
    Node* pred = predecessor(temp);
    printf("%d ", pred->val);

    return 0;
}