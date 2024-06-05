#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.c"

char string[888] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque felis ex, lacinia sed ligula eget, mattis commodo nunc. Quisque quis ex dapibus metus dignissim viverra. Proin id ultrices diam. Suspendisse tempor, mi vitae tempor tempus, nisi est auctor lorem, sed accumsan orci lectus rhoncus orci. Cras eget fermentum lacus, et facilisis felis. Curabitur tellus nisi, porta eu eleifend vitae, mattis eget mauris. Sed quis augue eget ex congue efficitur a et libero. Sed neque turpis, ultricies malesuada aliquet quis, dictum sit amet eros. Nulla facilisi. Pellentesque ac vehicula sapien. Pellentesque suscipit ligula ut erat finibus, non euismod odio fringilla. Maecenas ac nisi id ex sagittis egestas. Vivamus consectetur, sem in ultrices consectetur, enim risus rutrum mauris, a vulputate lectus sapien vel elit. Vivamus pretium augue nulla, sed feugiat turpis vestibulum eget.";
int freq[255] = {0};

typedef struct Node {
    char *data;
    int freq;
    struct Node *left, *right;
} Node;

Node *createNode(char *data, int freq) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int isLeaf(Node* root) {
    return root->left == NULL && root->right == NULL;
}

void print(Node *root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        print(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        print(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

int main() {

    for(int i = 0; i < strlen(string); i++)
        freq[(int)string[i]]++;

    PQueue *pq = init_pq();

    for(int i = 0; i < 255; i++) {
        if (freq[i] > 0) {
            Node* node = createNode((char)i, freq[i]);
            pqInsert(pq, (void*)node, (float)node->freq);
        }
    }

    while(pq->size > 1) {
        PQNode *left = deleteMin(pq);
        PQNode *right = deleteMin(pq);

        Node *leftNode = (Node *)left->data;
        Node *rightNode = (Node *)right->data;

        Node *newNode = createNode(NULL, leftNode->freq + rightNode->freq);
        newNode->left = leftNode;
        newNode->right = rightNode;

        pqInsert(pq, (void*)newNode, (float)newNode->freq);
    }

    PQNode *root = deleteMin(pq);

    int arr[100], top = 0;
    print((Node *)root->data, arr, top);

    return 0;
}