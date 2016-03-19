<<<<<<< HEAD
#include "avl.h"
 
int height(struct node *n) {
=======
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"

typedef struct nodeAVL {
    char* string;
    struct nodeAVL *left;
    struct nodeAVL *right;
    int height;
}node;

static int height(AVL n) {
>>>>>>> a566039f6dbd95990dc62c0cde784d75f2eb0412
    if (n == NULL)
        return 0;
    return n->height;
}
 
<<<<<<< HEAD
int max(int a, int b) {
=======
static int max(int a, int b) {
>>>>>>> a566039f6dbd95990dc62c0cde784d75f2eb0412
    return (a > b)? a : b;
}


<<<<<<< HEAD
struct node* newNode(char* info) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
=======
static AVL newNode(char* info) {
    struct nodeAVL* node = (struct nodeAVL*) malloc(sizeof(struct nodeAVL));
>>>>>>> a566039f6dbd95990dc62c0cde784d75f2eb0412
    node->string = malloc(32);
    strcpy(node->string,info);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}


<<<<<<< HEAD
struct node *rightRotate(struct node *y) {

    struct node *x = y->left;
    struct node *T2 = x->right;
=======
static AVL rightRotate(AVL y) {

    AVL x = y->left;
    AVL T2 = x->right;
>>>>>>> a566039f6dbd95990dc62c0cde784d75f2eb0412
 
    x->right = y;
    y->left = T2;
 
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}


<<<<<<< HEAD
struct node *leftRotate(struct node *x) {

    struct node *y = x->right;
    struct node *T2 = y->left;
 
    /* Perform rotation */
    y->left = x;
    x->right = T2;
 
    /* Update heights */
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    /* Return new root */
=======
static AVL leftRotate(AVL x) {

    AVL y = x->right;
    AVL T2 = y->left;
 

    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
>>>>>>> a566039f6dbd95990dc62c0cde784d75f2eb0412
    return y;
}


<<<<<<< HEAD
/* Get Balance factor of node N */

int getBalance(struct node *N) {
=======

static int getBalance(AVL N) {
>>>>>>> a566039f6dbd95990dc62c0cde784d75f2eb0412
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 

<<<<<<< HEAD
struct node* insert(struct node* node, char* info) {
    /*  Inserção do nodo */
=======
AVL insert(AVL node, char* info) {

>>>>>>> a566039f6dbd95990dc62c0cde784d75f2eb0412
    if (node == NULL)
        return(newNode(info));
 
    if (strcmp(info,node->string) < 0)
        node->left  = insert(node->left, info);
    else
        node->right = insert(node->right, info);
 
    /* Atualiza os pesos */
    node->height = max(height(node->left), height(node->right)) + 1;
 
    /* Varifica o balanceamento */
    int balance = getBalance(node);
 
<<<<<<< HEAD
    /* Caso esteja não balanceada, aplica o caso correspondente. */
 
=======
>>>>>>> a566039f6dbd95990dc62c0cde784d75f2eb0412
    /* Left Left Case */
    if (balance > 1 && strcmp(info,node->left->string) < 0)
        return rightRotate(node);
 
    /* Right Right Case */
    if (balance < -1 && strcmp(info,node->right->string) > 0)
        return leftRotate(node);
 
    /* Left Right Case */
    if (balance > 1 && strcmp(info,node->left->string) > 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
     /* Right Left Case */
    if (balance < -1 && strcmp(info, node->right->string) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}

<<<<<<< HEAD
int lookUp(struct node *node, char* value) {
=======
int lookUp(AVL node, char* value) {
>>>>>>> a566039f6dbd95990dc62c0cde784d75f2eb0412
    int r;
    if(node == NULL) return 0;
    else {
        r = strcmp(value,node->string);
        if(r == 0) return 1;
        else if(r < 0) lookUp(node->left, value);
        else lookUp(node->right,value);
    }
}


<<<<<<< HEAD
void preOrder(struct node *root)
=======
void preOrder(AVL root)
>>>>>>> a566039f6dbd95990dc62c0cde784d75f2eb0412
{
    if(root != NULL)
    {
        printf("%s\n", root->string);
        preOrder(root->left);
        preOrder(root->right);
    }
}