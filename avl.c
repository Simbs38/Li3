#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"

/* Estrutura definida para um nodo de uma AVL */

typedef struct nodeAVL {
    char* string;
    struct nodeAVL *left;
    struct nodeAVL *right;
    int height;
}node;


CATALOG init_catalog(){

    CATALOG catalogo = (struct catalog*) malloc(sizeof(struct catalog));
    int i;
    for(i = 0; i < 26; i++) {
        catalogo->letras[i] = NULL;
    }
    
    return catalogo;
}


/* Função que devolve a altura de um dado nodo de uma AVL */

static int height(AVL n) {
    if (n == NULL)
        return 0;
    return n->height;
}
 
static int max(int a, int b) {
    return (a > b)? a : b;
}

/* Função responsavel pela criação de um novo nodo */

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
    
    /* Rotações */

    x->right = y;
    y->left = T2;
    
    /* Atualização dos pesos dos nodos */

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}


static AVL leftRotate(AVL x) {

    AVL y = x->right;
    AVL T2 = y->left;
 
    /* Rotações */

    y->left = x;
    x->right = T2;
 
    /* Atualização dos pesos dos nodos */

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    return y;
}

/* Retorna o balanceamento da arvore, estando a arvore balanceada para valores retornados entre -1 e 1 */

static int getBalance(AVL N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
/* Função com o objetivo de inserir uma nova informação na arvore */

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

/* Função que tem como funcionalidade a procura de um dado elemento na AVL */

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