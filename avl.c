#include "avl.h"
#include "valida.h"
#include "main.h"
 
int height(struct node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}
 
int max(int a, int b) {
    return (a > b)? a : b;
}


struct node* newNode(char* info) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->string = malloc(32);
    strcpy(node->string,info);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}


struct node *rightRotate(struct node *y) {

    struct node *x = y->left;
    struct node *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}


struct node *leftRotate(struct node *x) {

    struct node *y = x->right;
    struct node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}


// Get Balance factor of node N

int getBalance(struct node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 

struct node* insert(struct node* node, char* info) {
    /*  Inserção do nodo */
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
 
    // Caso esteja não balanceada, aplica o caso correspondente.
 
    // Left Left Case
    if (balance > 1 && strcmp(info,node->left->string) < 0)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && strcmp(info,node->right->string) > 0)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && strcmp(info,node->left->string) > 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
     // Right Left Case
    if (balance < -1 && strcmp(info, node->right->string) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}

int lookUp(struct node *node, char* value) {
    int r;
    if(node == NULL) return 0;
    else {
        r = strcmp(value,node->string);
        if(r == 0) return 1;
        else if(r < 0) lookUp(node->left, value);
        else lookUp(node->right,value);
    }
}


void preOrder(struct node *root)
{
    if(root != NULL)
    {
        printf("%s\n", root->string);
        preOrder(root->left);
        preOrder(root->right);
    }
}