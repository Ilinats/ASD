#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "tree.h"

Node *create_tree_node(int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node *insert(Node *root, int val) {
    if(root == NULL)
        return create_tree_node(val);

    if(val % 2 == root->val % 2) {
        if (val < root->val)
            root->left = insert(root->left, val);
        else if (val > root->val)
            root->right = insert(root->right, val);
    } else if (val % 2 == 0)
        root->right = insert(root->right, val);
    else
        root->left = insert(root->left, val);

    return root;
}

void bustrophedon_traversal(Node *root) {
    if(root == NULL)
        return;

    Stack *curLevel = init_stack();
    Stack *nextLev = init_stack();
    push(curLevel, root);

    int isReserved = 0;

    while(curLevel->top != NULL) {
        Node *top = pop(curLevel);
        if(top != NULL)
            printf("%d ", top->val);

        if(isReserved) {
            if(root->right != NULL)
                push(nextLev, root->right);

            if(root->left != NULL)
                push(nextLev, root->left);
        } else {
            if(root->left != NULL)
                push(nextLev, root->left);
            
            if(root->right != NULL)
                push(nextLev, root->right);
        }

        if(curLevel->top == NULL) {
            isReserved = !isReserved;
            Stack *tem = curLevel;
            curLevel = nextLev;
            nextLev = tem;
        }
    }
}

void inorder(Node *root) {
    if(root == NULL) 
        return;

    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}