#include <stdio.h>
#include <stdlib.h>
#define SIZE 9

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

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *tree) {
    if(tree == NULL)
        return 0;

    return 1 + max(height(tree->left), height(tree->right));
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int heightFromRoot(Node* tree, Node* target) {
    if (tree == NULL)
        return 0;

    if (tree == target)
        return 1;

    int leftHeight = heightFromRoot(tree->left, target);
    int rightHeight = heightFromRoot(tree->right, target);

    if (leftHeight > 0 || rightHeight > 0)
        return 1 + max(leftHeight, rightHeight);
    else
        return 0;
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

Node *findMin(Node *tree) {
    if(tree->left == NULL)
        return tree;

    findMin(tree->left);
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

Node* successor(Node* tree) {
    if(tree->right != NULL)
        return findMin(tree->right);

    Node* parent = tree->parent;
    while (parent != NULL && tree == parent->right) {
        tree = parent;
        parent = parent->parent;
    }
    
    return parent->left;
}

Node* commonPredecessor(Node* node1, Node* node2, Node* tree) {
    int height1 = heightFromRoot(tree, node1);
    int height2 = heightFromRoot(tree, node2);

    if(height1 == height2 && node1 != NULL && node2 != NULL) {
        if(node1->val == node2->val)
            return node1;
        else
            commonPredecessor(node1->parent, node2->parent, tree);
    }
    else if(height1 > height2)
        commonPredecessor(node1->parent, node2, tree);
    else if(height2 > height1)
        commonPredecessor(node1, node2->parent, tree);
}

void commonPredecessorHelper(Node* tree) {
    Node* node1 = getNodeByVal(tree, 11);
    Node* node2 = getNodeByVal(tree, 17);
    Node* temp = commonPredecessor(node1, node2, tree);
    printf("%d\n", temp->val);
}

int isHeapFromArr(int* arr) {
    int parent = 0;

    while(parent < SIZE) {
        int child = 2*parent + 1;

        if(child < SIZE && child+1 < SIZE)
            if(arr[child] < arr[child+1])
                child ++;

        if(child < SIZE && arr[parent] < arr[child])
            return 0;
        else 
            parent++;
    }

    return 1;
}

void insertInHeap(int *heap, int size, int value) {
    if (size == 0) {
        printf("Heap is full\n");
        return;
    }

    int i = size;
    heap[i] = value;

    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void mergeHeaps(int *heap1, int *heap2, int *heap3) {
    for (int i = 0; i < SIZE; i++)
        heap3[i] = heap1[i];

    for (int i = 0; i < SIZE; i++)
        insertInHeap(heap3, SIZE + i, heap2[i]);
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
    Node* next = successor(temp);
    Node* prev = predecessor(temp);
    printf("%d, %d\n", prev->val, next->val);

    commonPredecessorHelper(tree);

    int arr2[SIZE] = {50, 25, 56, 20, 34, 65, 5, 24, 27};
    printf("Is heap?: %s\n", isHeapFromArr(arr2) ? "Yes" : "No");
    int arr3[SIZE] = {50, 25, 32, 20, 13, 23, 5, 2, 1};
    printf("Is heap?: %s\n", isHeapFromArr(arr3) ? "Yes" : "No");

    int heap1[SIZE] = {9, 7, 8, 5, 6, 4, 3, 1, 2};
    int heap2[SIZE] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    int heap3[SIZE * 2];
    mergeHeaps(heap1, heap2, heap3);
    printf("Merged Heap: ");
    for (int i = 0; i < SIZE * 2; i++)
        printf("%d ", heap3[i]);
    printf("\n");

    printf("Is heap?: %s\n", isHeapFromArr(heap3) ? "Yes" : "No");

    return 0;
}