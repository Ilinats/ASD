#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node **children;
    int childrenCount;
    struct node *parent;
} Node;

Node *createNode(int val) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->val = val;
    node->childrenCount = 0;
    node->children = NULL;
    node->parent = NULL;

    return node;
}

void insert(Node *root, int parentVal, int val) {
    if(root == NULL)
        return;

    if(root->val == parentVal) {
        if(root->children == NULL)
            root->children = (Node **) malloc(sizeof(Node *) * 1);
        else
            root->children = (Node **) realloc(root->children, sizeof(Node *) * (root->childrenCount + 1));

        root->children[root->childrenCount++] = createNode(val);
        root->children[root->childrenCount - 1]->parent = root;
        return;
    }

    for (int i = 0; i < root->childrenCount; i++)
        insert(root->children[i], parentVal, val);

}

void inorderTraversal(Node* root) {
    if (root == NULL) 
        return;

    for(int i = 0; i < root->childrenCount - 1; i++)
        inorderTraversal(root->children[i]);

    printf("%d ", root->val);

    if(root->childrenCount > 0)
        inorderTraversal(root->children[root->childrenCount - 1]);
}

void bfsTraversal(Node* root) {
    if (root == NULL)
        return;

    Node** queue = (Node**)malloc(sizeof(Node*));
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Node* currentNode = queue[front++];

        printf("%d ", currentNode->val);

        for (int i = 0; i < currentNode->childrenCount; ++i) {
            if (currentNode->children[i] != NULL) {
                queue = (Node**)realloc(queue, (rear + 1) * sizeof(Node*));
                queue[rear++] = currentNode->children[i];
            }
        }
    }

    free(queue);
}

void dfsTraversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->val);

        for (int i = 0; i < root->childrenCount; ++i)
            dfsTraversal(root->children[i]);
    }
}

void printTree(Node* root, int depth) {
    if (root != NULL) {
        for (int i = 0; i < depth; ++i) {
            printf("  ");
        }
        printf("%d\n", root->val);

        for (int i = 0; i < root->childrenCount; ++i) {
            printTree(root->children[i], depth + 1);
        }
    }
}

void leftViewUtil(Node* root, int level, int* maxLevel) {
    if (root == NULL) {
        return;
    }

    if (level > *maxLevel) {
        printf("%d ", root->val);
        *maxLevel = level;
    }

    for (int i = 0; i < root->childrenCount; ++i) {
        leftViewUtil(root->children[i], level + 1, maxLevel);
    }
}

void leftView(Node* root) {
    int maxLevel = -1;
    printf("Left View: ");
    leftViewUtil(root, 0, &maxLevel);
    printf("\n");
}

void rightViewUtil(Node* root, int level, int* maxLevel) {
    if (root == NULL) {
        return;
    }

    if (level > *maxLevel) {
        printf("%d ", root->val);
        *maxLevel = level;
    }

    for (int i = root->childrenCount - 1; i >= 0; --i) {
        rightViewUtil(root->children[i], level + 1, maxLevel);
    }
}

void rightView(Node* root) {
    int maxLevel = -1;
    printf("Right View: ");
    rightViewUtil(root, 0, &maxLevel);
    printf("\n");
}

int main() {

    Node *root = createNode(1);
    insert(root, 1, 2);
    insert(root, 1, 3);
    insert(root, 1, 4);
    insert(root, 2, 5);
    insert(root, 2, 6);
    insert(root, 3, 7);
    insert(root, 3, 8);
    insert(root, 4, 9);

    inorderTraversal(root);
    printf("\n");
    bfsTraversal(root);
    printf("\n");
    dfsTraversal(root);
    printf("\n");
    //printTree(root, 0);
    leftView(root);
    rightView(root);

    return 0;
}