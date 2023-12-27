#ifndef _STACK_H_
#define _STACK_H_

typedef struct Node Node;

typedef struct StackNode
{
    Node *val;
    struct StackNode *next;
} StackNode;

typedef struct Stack
{
    StackNode *top;
} Stack;

StackNode *create_stack_node(Node *val);
Stack *init_stack();

void push(Stack *stack, Node *val);
Node* pop(Stack *stack);
void clear_stack(Stack *stack);
void print_stack(Stack *stack);

#endif