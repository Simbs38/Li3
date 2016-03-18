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
    if (n == NULL)
        return 0;
    return n->height;
}
 
static int max(int a, int b) {
    return (a > b)? a : b;
}


static AVL newNode(char* info) {
    struct nodeAVL* node = (struct nodeAVL*) malloc(sizeof(struct nodeAVL));
    node->string = malloc(32);
    strcpy(node->string,info);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}


static AVL rightRotate(AVL y) {

    AVL x = y->left;
    AVL T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}


static AVL leftRotate(AVL x) {

    AVL y = x->right;
    AVL T2 = y->left;
 

    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    return y;
}



static int getBalance(AVL N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 

AVL insert(AVL node, char* info) {

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

int lookUp(AVL node, char* value) {
    int r;
    if(node == NULL) return 0;
    else {
        r = strcmp(value,node->string);
        if(r == 0) return 1;
        else if(r < 0) lookUp(node->left, value);
        else lookUp(node->right,value);
    }
}


void preOrder(AVL root)
{
    if(root != NULL)
    {
        printf("%s\n", root->string);
        preOrder(root->left);
        preOrder(root->right);
    }
}