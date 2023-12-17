#include <stdio.h>
#include <stdlib.h>
#include "../vectors/vector.c"

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

Node *insertNode(Node *tree, int val)
{
    if (tree == NULL)
        return create_node(val);

    if (val < tree->val)
        tree->left = insertNode(tree->left, val);
    else if (val > tree->val)
        tree->right = insertNode(tree->right, val);

    return tree;
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

    int arr[2] = {11, 17};
    int sum = 0;
    printf("%d\n", sumInInterval(tree, arr, &sum));

    sum = 0;
    bstToGst(tree2, &sum);
    print(tree2);
    printf("\n");

    print(tree);

    return 0;
}