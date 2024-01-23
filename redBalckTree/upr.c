#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/*Колко най-много node-a може да има дърво с черна височина k? 2^(2k)-1
А най-малко? 2^(2k-1) - 1
Представете си, че съставяме Red Black Tree като вмъкваме елементи един по един в него. Възможно ли е да се построи дърво, 
в което да няма червени елементи? Само ако има един елемент - root-a, иначе не.*/

/* Условия:
1. Root-ът е черен
2. Наследниците на червените трябва да са черни
3. Листата (NULL) са черни
4. Всеки един път от корена надолу ще съдържат еднакъв брой черни node-ове */

/*Най-лош случай insert: О(logn + fixup) = О(2logn)
Най-добър случай insert: константен
Search - най-лош случай е O(h), т.е за redblack tree e О(2logn)*/

typedef enum Color {
    RED,
    BLACK
} Color;

typedef struct Node {
    int val;
    Color color;
    int blackHeight;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_tree_node(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = RED;
    node->blackHeight = 1;

    return node;
}

void inorderTraversal(Node *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d(%c) ", root->val, (root->color == BLACK ? 'B' : 'R'));

        inorderTraversal(root->right);
    }
}

void preorder(Node *root) {
    if (root != NULL) {
        printf("%d(%c) ", root->val, (root->color == BLACK ? 'B' : 'R'));
        preorder(root->left);
        preorder(root->right);
    }
}

void leftRotation(Node **root, Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    x->right = T2;
    y->left = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        (*root) = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;

    x->parent = y;

    if (T2 != NULL)
        T2->parent = x;
}

/*
     x                               y
    / \     Right Rotation          /  \
   y   T3   - - - - - - - >        T1   x
  / \       < - - - - - - -            / \
 T1  T2                               T2
*/

void rightRotation(Node **root, Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    y->left = T2;
    x->right = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        (*root) = x;
    else if (y->parent->left == y)
        y->parent->left = x;
    else
        y->parent->right = x;

    y->parent = x;

    if (T2 != NULL)
        T2->parent = y;
}

void treeFixup(Node **root, Node *x) {
    Node *gp = NULL;
    Node *uncle = NULL;

    while (x != (*root) && x->parent->color == RED) {
        gp = x->parent->parent;

        if (gp->left == x->parent) {
            uncle = gp->right;

            if (uncle != NULL && uncle->color == RED) {
                x->parent->color = BLACK;
                uncle->color = BLACK;
                gp->color = RED;

                x = gp;
            } else {
                if (x->parent->right == x) {
                    x = x->parent;
                    leftRotation(root, x);
                }

                x->parent->color = BLACK;
                gp->color = RED;
                rightRotation(root, gp);
            }
        } else {
            uncle = gp->left;

            if (uncle != NULL && uncle->color == RED) {
                x->parent->color = BLACK;
                uncle->color = BLACK;
                gp->color = RED;

                x = gp;
            } else {
                if (x->parent->left == x) {
                    x = x->parent;
                    rightRotation(root, x);
                }

                x->parent->color = BLACK;
                gp->color = RED;
                leftRotation(root, gp);
            }
        }
    }

    (*root)->color = BLACK;
}

void updateBlackHeight(struct Node* node) {
    if (node == NULL) return;

    int leftHeight = (node->left != NULL) ? node->left->blackHeight : 0;
    int rightHeight = (node->right != NULL) ? node->right->blackHeight : 0;

    node->blackHeight = (node->color == RED) ? MAX(leftHeight, rightHeight) : MAX(leftHeight, rightHeight) + 1;

    updateBlackHeight(node->parent);
}

void insert(Node **root, int val) {
    Node *new_node = create_tree_node(val);
    Node *current = *root;

    if (current == NULL) {
        new_node->color = BLACK;
        *root = new_node;
        return;
    }

    while (1) {
        if (current->val > val) {
            if (current->left == NULL)
                break;

            current = current->left;
        } else {
            if (current->right == NULL)
                break;

            current = current->right;
        }
    }

    if (current->val > val)
        current->left = new_node;
    else
        current->right = new_node;

    new_node->parent = current;

    treeFixup(root, new_node);
    updateBlackHeight(new_node);
}

int getBH(Node *root) {
    int bh = 1;

    while (root != NULL) {
        if (root->color == BLACK)
            bh++;

        root = root->right;
    }

    return bh;
}

int isRBTreeR(Node *root, int bh) {
    if (root == NULL)
        return bh == 1;

    if (root->color == RED && ((root->left != NULL && root->left->color == RED) || (root->right != NULL && root->right->color == RED)))
        return 0;

    if (root->color == BLACK)
        bh--;

    return isRBTreeR(root->left, bh) && isRBTreeR(root->right, bh);
}

int isRBTree(Node *root) {
    if (root == NULL)
        return 1;

    if (root->color == RED)
        return 0;

    int bh = getBH(root); // O(n), O(logn) ako e RBTree

    return isRBTreeR(root, bh); // n

    // Result: O(n) + O(n) = O(n)
}

// Дадено е червено-черно дърво и две числа x и y. Да се принтират всички числа между тях. Каква е сложността? O(logn + k), k - брой числа в интервала

void printInRange(Node *root, int a, int b) {
    if (root == NULL)
        return;

    if (root->val >= a && root->val <= b) {
        printInRange(root->left, a, b);
        printf("%d ", root->val);
        printInRange(root->right, a, b);
    } else if (root->val < a)
        printInRange(root->right, a, b);
    else
        printInRange(root->left, a, b);
}

int main()
{
    struct Node *root = NULL;

    insert(&root, 7);
    insert(&root, 3);
    insert(&root, 18);
    insert(&root, 10);
    insert(&root, 22);
    insert(&root, 8);
    insert(&root, 11);
    insert(&root, 26);

    inorderTraversal(root);
    printf("\n");

    leftRotation(&root, root);
    preorder(root);
    printf("\n");

    rightRotation(&root, root);
    preorder(root);
    printf("\n");

    printInRange(root, 5, 20);

    return 0;
}