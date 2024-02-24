#include <stdlib.h>
#include <stdio.h>
 
typedef enum Color
{
    RED,
    BLACK
} Color;
 
typedef struct Node
{
    int val;
    Color color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;
 
Node *create_tree_node(int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = RED;
 
    return node;
}
 
void inorderTraversal(Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d(%c) ", root->val, (root->color == BLACK ? 'B' : 'R'));
 
        inorderTraversal(root->right);
    }
}
 
void preorderTraversal(Node *root)
{
    if (root != NULL)
    {
        printf("%d(%c) ", root->val, (root->color == BLACK ? 'B' : 'R'));
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}
 
/*
     x                               y
    / \     Right Rotation          /  \
   y   T3   - - - - - - - >        T1   x
  / \       < - - - - - - -            / \
 T1  T2                               T2  T3
*/
 
void leftRotation(Node **root, Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    x->right = T2;
    y->left = x;
 
    y->parent = x->parent;
 
    if (x->parent == NULL)
    {
        (*root) = y;
    }
    else if (x->parent->left == x)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
 
    x->parent = y;
 
    if (T2 != NULL)
    {
        T2->parent = x;
    }
}
 
void rightRotation(Node **root, Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    y->left = T2;
    x->right = y;
 
    x->parent = y->parent;
 
    if (y->parent == NULL)
    {
        (*root) = x;
    }
    else if (y->parent->left == y)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
 
    y->parent = x;
 
    if (T2 != NULL)
    {
        T2->parent = y;
    }
}
 
void treeFixup(Node **root, Node *x)
{
    Node *gp = NULL;
    Node *uncle = NULL;
 
    while (x != (*root) && x->parent->color == RED)
    {
        gp = x->parent->parent;
 
        if (gp->left == x->parent)
        {
            uncle = gp->right;
 
            if (uncle != NULL && uncle->color == RED)
            {
                x->parent->color = BLACK;
                uncle->color = BLACK;
                gp->color = RED;
 
                x = gp;
            }
            else
            {
                if (x->parent->right == x)
                {
                    x = x->parent;
                    leftRotation(root, x);
                }
 
                x->parent->color = BLACK;
                gp->color = RED;
                rightRotation(root, gp);
            }
        }
        else
        {
            uncle = gp->left;
 
            if (uncle != NULL && uncle->color == RED)
            {
                x->parent->color = BLACK;
                uncle->color = BLACK;
                gp->color = RED;
 
                x = gp;
            }
            else
            {
                if (x->parent->left == x)
                {
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

void insert(Node **root, int val)
{
    Node *new_node = create_tree_node(val);
    Node *current = *root;
 
    if (current == NULL)
    {
        new_node->color = BLACK;
        *root = new_node;
        return;
    }
 
    while (1)
    {
        if (current->val > val)
        {
            if (current->left == NULL)
            {
                break;
            }
            current = current->left;
        }
        else
        {
            if (current->right == NULL)
            {
                break;
            }
            current = current->right;
        }
    }
 
    if (current->val > val)
    {
        current->left = new_node;
    }
    else
    {
        current->right = new_node;
    }
 
    new_node->parent = current;
 
    treeFixup(root, new_node);
}
 
int getBH(Node *root)
{
    int count = 1;

    while(root) {
        if(root->color == BLACK)
            count++;

        root = root->right;
    }
}

Node* findSmallestWithBH(Node* root, int bh) {
    Node* current = root;

    int height = getBH(current);

    while (current && height > bh) {
        if(current->color == BLACK)
            height--;
        
        current = current->left;
    }

    return current;
}
 
Node* joinTrees(Node* t1, Node* t2, int x) {
    int t2BH = getBH(t2);

    Node *y = findSmallestWithBH(t1, t2BH);

    Node *TY = y->right;

    Node* root = create_tree_node(x);
    root->right = TY;

    root->val = x;
    root->color = RED;
    root->right = TY;
    root->left = t2;
    root->parent = y;

    if(y)
        y->right = root;
    else
        t1 = root;

    treeFixup(&t1, root);

    return t1;

}

int isRBTreeHelper(Node *root, int bh) {
    if (root)
        return bh == 1;

    if (root->color == RED && ((root->left && root->left->color == RED) || (root->right && root->right->color == RED)))
        return 0;

    if (root->color == BLACK)
        bh--;

    return isRBTreeHelper(root->left, bh) && isRBTreeHelper(root->right, bh);
}
 
int isRBTree(Node *root)
{
    if(root->color == RED) 
        return 0;

    int bh = getBH(root);

    isRBTreeHelper(root, bh);
}
 
int main()
{
    struct Node *root = NULL;
 
    insert(&root, 7);
    insert(&root, 3);
    insert(&root, 18);
    insert(&root, 28);
    insert(&root, 32);
    insert(&root, 52);
    insert(&root, 41);
    insert(&root, 35);
    insert(&root, 65);
    insert(&root, 27);
    insert(&root, 17);
    insert(&root, 99);
    insert(&root, 88);
 
 
    struct Node *root2 = NULL;
 
    insert(&root2, 101);
    insert(&root2, 150);
    insert(&root2, 180);
    insert(&root2, 280);
    insert(&root2, 320);
    insert(&root2, 520);
    insert(&root2, 410);
 
    struct Node *joinned = joinTrees(root, root2, 100);
 
    inorderTraversal(joinned);
 
    if (isRBTree(joinned)) {
      printf("yes");
    }
 
    return 0;
}
 
/*
Задача1:
    Защото, ако винаги го правим черен ще променяме при всеки insert черната височина ще се променя, тоест цялото дърво трябва да бъде
    обходено, проверено и ако е нужно променено, за да може да продължи да изпълнява условията за rbtree.
 
Задача2:
    Най-малкият възможен брой връзки е една, ако червените нямат деца, а иначе общо 5, ако и двете червени са имали по две деца.
    Дълбочината може да се намали максимално до 2 пъти, ако децата на всеки един черен node са червени. Дълбочината става
    равна на черната височина на дървото.

Задача3:
 за AVL дървото:
    Не може, защото най-вдясно, най-десния node на ниво 4 има 2 леви деца. Лявото дете на неговия родител има 0 леви деца,
    тоест се получава разлика от 2, което е невалидно за AVL дърветата.
 
 za RB дървото:
    Това дърво може да е валидно RBT, защото във всеки случай 0 трябва да е черна(корен). Допускаме, че 1 и 2 са черни, 
    както и че 3 също е черно. Така черната височина става максимално 3. Ако оцветим 4 ччервено и 59 и 58 в черно, то тогава имаме
    път с 3 черни. Ако 5 и 6 са ервени, то съответно 57, 60, 56 и 14 трябва да са черни (но-необходимост). ТОгава техните деца 61 и 16 
    ще станат червени, следователно пътищата отново ще имат черна височина 3, тоест е валидно дърво.

Задача4:
 какъв да бъде цвета на новия node и как да оправим нередности?
 (ако сте писали кода се подразбира, но за който не е може все пак да се опита да отговори)
    Цветът на новия node трябва да е червен, за да не се нарушава черната височина на дървото. Това обаче може да доведе до
    червени деца на червен родител. Ако е черен ще се развали височината и ще трябва да се правят ротации и размени на цветовете
    из цялото дърво.

 каква е сложността на join-а?
    O(logn) при n = сумата на броя на елементите на първото и второто дърво. Добавянето на x е O(logn), treeFixUp също е O(logn),
    тоест O(2logn), което си е O(logn).
 
*/