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

void fillVector(Node *tree, vector_t *vector) {
    if(tree == NULL)
        return;

    fillVector(tree->left, vector);
    push_back(vector, tree->val);
    fillVector(tree->right, vector);
}

Node *buildTreeRect(vector_t *v, int start, int end) {
    if(start > end)
        return NULL;

    int mid = (start + end) / 2;
    Node *node = create_node(v->arr[mid]);

    node->left = buildTreeRect(v, start, mid - 1);
    node->right = buildTreeRect(v, mid + 1, end);

    return node;
}

Node *buildTree(vector_t *v) {
    Node *root = NULL;
    root = buildTreeRect(v, 0, v->size - 1);

    return root;
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

void printByLevelsHelper(Node *tree, int level) {
    if(tree == NULL)
        return;

    if(level == 1)
        printf("%d ", tree->val);
    else if(level > 1) {
        printByLevelsHelper(tree->left, level - 1);
        printByLevelsHelper(tree->right, level - 1);
    }
}

void printByLevels(Node *tree) {
    printf("%d ", tree->val);
    int h = height(tree);
    for(int i = 2; i <= h; i++)
        printByLevelsHelper(tree, i);
}

Node* buildFromPostOrder(int *arr, int start, int end) {
    if(start > end)
        return NULL;

    Node* tree = create_node(arr[end]);
    int mid = end - 1;

    while(arr[mid] > tree->val && mid >= start)
        mid--;
    
    tree->left = buildFromPostOrder(arr, start, mid);
    tree->right = buildFromPostOrder(arr, mid + 1, end - 1);

    return tree;
}

int main() {
    Node *tree = create_node(9);
    insertNode(tree, 15);
    insertNode(tree, 7);
    insertNode(tree, 13);
    insertNode(tree, 11);
    insertNode(tree, 6);
    insertNode(tree, 8);

    //int arr[16] = {0, 1, 4, 6, 9, 5, 17, 16, 25, 27, 44, 42, 56, 34, 20, 10};
    int arr[16] = {0, 1, 4, 34, 20, 10};
    Node *tree2;
    //tree2 = buildFromPostOrder(arr, 0, 14, arr[15]);
    tree2 = buildFromPostOrder(arr, 0, 5);
    print(tree2);

    // print(tree);
    // printf("\n");
    // printByLevels(tree);

    return 0;
}