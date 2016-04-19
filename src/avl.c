#include "./headers/avl.h"

#include <stdlib.h>
#include <string.h>


struct nodeAVL {
    char string[10];
    void *cont;
    struct nodeAVL *left;
    struct nodeAVL *right;
    int height;
};


struct avl {
    NODO arvore;
    int avl_tamanho; 
};


static int height(NODO n);
static int max(int a, int b);
static int getBalance(NODO N);
static Boolean node_lookUp(NODO node, Valor value);
static NODO newNode(NODO node, Valor info, void *estrutura);
static NODO rightRotate(NODO y);
static NODO leftRotate(NODO x);
static NODO atualiza_node(NODO node, char* value, void* estrutura);
static NODO node_insert(NODO node, Valor string, Estrutura estrutura);
static NODO tree_clone(NODO node);
static Estrutura node_getEstrutura(NODO node, Valor value);
static void tree_free(NODO node);


AVL initAVL() {
    AVL tree = malloc(sizeof(struct avl));
    tree->arvore = NULL;
    tree->avl_tamanho = 0;
    return tree;
}

AVL atualiza_avl(AVL tree, char* value, Estrutura estrutura) {
    tree->arvore = atualiza_node(tree->arvore,value,estrutura);
    return tree;
}


AVL avl_insert(AVL tree, Valor key, Estrutura estrutura) {
    tree->arvore = node_insert(tree->arvore,key,estrutura);
    tree->avl_tamanho ++;
    return tree;
}


Boolean avl_lookUp(AVL tree, Valor value) {
    if(tree==NULL) return false;
    return node_lookUp(tree->arvore,value);
}


int avl_count(AVL tree) {
    return tree->avl_tamanho;
}


AVL avl_clone(AVL node) {
    AVL tree = malloc(sizeof(struct avl));
    tree->arvore = tree_clone(node->arvore);
    tree->avl_tamanho = node->avl_tamanho;
    return tree;  
}


Estrutura avl_getEstrutura(AVL node, Valor value) {
    return node_getEstrutura(node->arvore,value);
}


NODO getNodo(AVL a) {
    return a->arvore;
}


NODO getNodoEsq(NODO n) {
    return n->left;
}


NODO getNodoDir(NODO n) {
    return n->right;
}


char* getString(NODO n) {
    char* novo;
    novo = malloc(10);
    strcpy(novo,n->string);
    return novo;
}


void* getCont(NODO n) {
    return n->cont;
}


void avl_free(AVL nodo) {
    tree_free(nodo->arvore);
    free(nodo);
}


static int height(NODO n) {
    if (n == NULL)
        return 0;
    return n->height;
}


static int max(int a, int b) {
    return (a > b)? a : b;
}


static NODO newNode(NODO node, Valor info, void *estrutura) {
    node = (NODO) malloc(sizeof(struct nodeAVL));
    strcpy(node->string,info);
    node->cont = estrutura;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return node;
}


static NODO rightRotate(NODO y) {

    NODO x = y->left;
    NODO T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}


static NODO leftRotate(NODO x) {

    NODO y = x->right;
    NODO T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    return y;
}


static int getBalance(NODO N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 

static NODO node_insert(NODO node, Valor info, Estrutura estrutura) {
    int balance;

    if(node != NULL) {

    if (strcmp(info,node->string) < 0)
        node->left  = node_insert(node->left, info, estrutura);
    else if(strcmp(info,node->string) > 0)
        node->right = node_insert(node->right, info, estrutura);
    else node->cont = estrutura;
    
    /* Atualiza os pesos */
    node->height = max(height(node->left), height(node->right)) + 1;
 
    /* Varifica o balanceamento */
    balance = getBalance(node);
 
    /* Left Left Case */
    if (balance > 1 && strcmp(info,node->left->string) < 0) return rightRotate(node);
 
    /* Right Right Case */
    if (balance < -1 && strcmp(info,node->right->string) > 0) return leftRotate(node);
 
    /* Left Right Case */
    if (balance > 1 && strcmp(info,node->left->string) > 0) {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
     /* Right Left Case */
    if (balance < -1 && strcmp(info, node->right->string) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    } else node = newNode(node,info,estrutura);
   
   return node;
}

static Boolean node_lookUp(NODO node, Valor value) {
    int r;
    if(node == NULL) return false;
    else {
        r = strcmp(value,node->string);
        if(r == 0) return true;
        else if(r < 0) node_lookUp(node->left, value);
        else node_lookUp(node->right,value);
    }
}

static NODO tree_clone(NODO node) {
    
    NODO aux;
    if(node) {
        aux = malloc(sizeof(struct nodeAVL));
        strcpy(aux->string,node->string); 
        aux->height = node->height;
        aux->cont = NULL;
        aux->left = tree_clone(node->left);
        aux->right = tree_clone(node->right);
    }
    else aux = NULL;

    return aux;
}


static NODO atualiza_node(NODO node, char* value, Estrutura estrutura) {
    int r;
    r = strcmp(value,node->string);
    if(r == 0) {
        node->cont = estrutura; 
        return node;
    }
    else if(r < 0) atualiza_node(node->left, value,estrutura);
    else atualiza_node(node->right,value,estrutura);

    return node;
}

static Estrutura node_getEstrutura(NODO node, Valor value) {
    int r;
    if(node == NULL) return NULL;
    else {
        r = strcmp(value,node->string);
        if(r == 0) return node->cont;
        else if(r < 0) node_getEstrutura(node->left, value);
        else node_getEstrutura(node->right,value);
    }
}

static void tree_free(NODO node) {
    if(node != NULL) {
        tree_free(node->left);
        tree_free(node->right);
        free(node);
    }
}