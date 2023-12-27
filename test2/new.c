#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct StackNode
{
    Node *val;
    struct StackNode *next;
} StackNode;

typedef struct Stack
{
    StackNode *top;
} Stack;

StackNode *create_stack_node(Node *val)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->val = val;
    node->next = NULL;

    return node;
}

Stack *init_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;

    return stack;
}

void push(Stack *stack, Node *val)
{
    StackNode *node = create_stack_node(val);
    node->next = stack->top;
    stack->top = node;
}

Node *pop(Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("Stack is empty.\n");
        exit(1);
    }

    Node *val = stack->top->val;
    StackNode *tmp = stack->top;
    stack->top = stack->top->next;
    free(tmp);

    return val;
}

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
            if(top->left != NULL)
                push(nextLev, top->left);

            if(top->right != NULL)
                push(nextLev, top->right);
        } else {
            if(top->right != NULL)
                push(nextLev, top->right);
            
            if(top->left != NULL)
                push(nextLev, top->left);
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

int main()
{
    Node *root = create_tree_node(2);
    insert(root, 4);
    insert(root, 7);
    insert(root, 5);
    insert(root, 10);
    insert(root, 6);
    insert(root, 12);
    insert(root, 8);
    insert(root, 11);
    insert(root, 9);

    inorder(root);
    printf("\n");
    bustrophedon_traversal(root);

    return 0;
}