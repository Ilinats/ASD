int isHeap(Node* tree) {
    if(tree == NULL)
        return 1;

    if(tree->left != NULL && tree->left->val > tree->val)
        return 0;

    if(tree->right != NULL && tree->right->val > tree->val)
        return 0;

    if(!(isHeap(tree->left) && isHeap(tree->right)))
        return 0;

    return 1;
}

int isBSTHelper(Node *node, int min, int max) {
    if (node == NULL)
        return 1;

    if (node->val < min || node->val > max)
        return 0;

    return isBSTHelper(node->left, min, node->val - 1) &&
           isBSTHelper(node->right, node->val + 1, max);
}

void isBST(Node *tree) {
    int min = findMin(tree)->val;
    int max = findMax(tree)->val;
    
    int res = isBSTHelper(tree, min, max);

    if(res)
        printf("Is BST");
    else
        printf("Not BST");
}

void printByLevelsHelper(Node *tree, int level) {
    if(tree == NULL)
        return;

    if(level == 1)
        printf("%d ", tree->val);
    else if(level > 1) {
        printByLevelsHelper(tree->left, level - 1);
        printByLevelsHelper(tree->right, level - 1);
    }
}

void printByLevels(Node *tree) {
    printf("%d ", tree->val);
    int h = height(tree);
    for(int i = 2; i <= h; i++)
        printByLevelsHelper(tree, i);
}