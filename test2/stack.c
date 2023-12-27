#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

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

void clear_stack(Stack *stack)
{
    while (stack->top != NULL)
    {
        pop(stack);
    }

    free(stack);
}
