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

Node *findMin(Node *tree) {
    if(tree->left == NULL) {
        printf("%d", tree->val);
        return tree;
    }

    findMin(tree->left);
}

Node *findMax(Node *tree) {
    if(tree->right == NULL) {
        printf("%d", tree->val);
        return tree;
    }

    findMax(tree->right);
}

int isBSTHelper(Node *node, int min, int max) {
    if (node == NULL)
        return 1;

    if (node->val < min || node->val > max)
        return 0;

    return isBSTHelper(node->left, min, node->val - 1) &&
           isBSTHelper(node->right, node->val + 1, max);
}

void isBST(Node *tree) {
    int min = findMin(tree)->val;
    int max = findMax(tree)->val;
    
    int res = isBSTHelper(tree, min, max);

    if(res)
        printf("Is BST");
    else
        printf("Not BST");
}

void kthSmallestHelper(Node *root, int k, int *count, int *result) {
    if (root == NULL || *count >= k)
        return;

    kthSmallestHelper(root->left, k, count, result);
    (*count)++;

    if (*count == k) {
        *result = root->val;
        return;
    }

    kthSmallestHelper(root->right, k, count, result);
}

int kthSmallest(Node *root, int k) {
    int count = 0;
    int result = -1;
    kthSmallestHelper(root, k, &count, &result);

    return result;
}

void kthLargestHelper(Node *root, int k, int *count, int *result) {
    if (root == NULL || *count >= k)
        return;

    kthLargestHelper(root->right, k, count, result);
    (*count)++;

    if (*count == k) {
        *result = root->val;
        return;
    }

    kthLargestHelper(root->left, k, count, result);
}

int kthLargest(Node *root, int k) {
    int count = 0;
    int result = -1;
    kthLargestHelper(root, k, &count, &result);

    return result;
}

int isSameStructure(Node *tree1, Node *tree2) {
    if (tree1 == NULL && tree2 == NULL)
        return 1;

    if (tree1 == NULL || tree2 == NULL)
        return 0;

    return isSameStructure(tree1->left, tree2->left) && isSameStructure(tree1->right, tree2->right);
}
 
int main() {
    Node *tree = create_node(9);
    insertNode(tree, 15);
    insertNode(tree, 7);
    insertNode(tree, 13);
    insertNode(tree, 11);
    insertNode(tree, 6);
    insertNode(tree, 8);

    Node *tree2 = create_node(9);
    insertNode(tree2, 15);
    insertNode(tree2, 7);
    insertNode(tree2, 13);
    insertNode(tree2, 11);
    insertNode(tree2, 6);
    insertNode(tree2, 8);
    insertNode(tree2, 10);

    print(tree);
    printf("\n");
    printByLevels(tree);
    printf("\n");
    findMin(tree);
    printf("\n");
    printf("%d\n", kthSmallest(tree, 3));
    printf("%d\n", kthLargest(tree, 4));
    printf("Same structure? %s\n", isSameStructure(tree, tree2) ? "Yes" : "No");

    return 0;
}