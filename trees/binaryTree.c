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

tree* buildTree(int* inorder, int* preorder, int *rootIndex, int start, int end) {
    
    if (start > end)
        return NULL;

    tree* root = createNode(preorder[(*rootIndex)]);
    int targetPos;

    for (int i = start; i <= end; i++)
        if (inorder[i] == root->value) {
            targetPos = i;
            break;
        }

    (*rootIndex)++;

    root->left = buildTree(inorder, preorder, rootIndex, start, targetPos - 1);
    root->right = buildTree(inorder, preorder, rootIndex, targetPos + 1, end);

    return root;
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
    printf("\n");

    tree* root2;
    int preorder[18] = {0, 1, 6, 8, 9, 10, 11, 7, 2, 4, 5, 3, 13, 14, 15, 16, 17, 12};
    int inorder[18] = {1, 10, 9, 11, 8, 6, 7, 0, 4, 5, 2, 14, 13, 17, 16, 15, 3, 12};

    int rootIndex = 0;
    root2 = buildTree(inorder, preorder, &rootIndex, 0, 17);
    printPreorder(root2);

    return 0;
}
