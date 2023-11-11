typedef struct node {
    int data;
    struct node *npx;
} Node;

Node* XOR(Node *a, Node *b);
Node* initList();
Node* creatNode(Node **list, int data);
void freeList(Node **list);

void pushBack(Node **list, int data);
void pushFront(Node **list, int data);
void printList(Node *list);