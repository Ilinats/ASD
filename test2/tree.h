#ifndef _TREE_H_
#define _TREE_H_


typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_tree_node(int val);
Node* insert(Node* root, int val);
void bustrophedon_traversal(Node *root);
void inorder(Node * root);

#endif