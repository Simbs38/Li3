#include "avl.h"

/* Estrutura definida para um nodo de uma AVL */

struct nodeAVL {
    Valor string;
    void *cont;
    struct nodeAVL *left;
    struct nodeAVL *right;
    int height;
};


static int height(AVL n);
static int max(int a, int b);
static AVL newNode(Valor info, void *estrutura);
static AVL rightRotate(AVL y);
static AVL leftRotate(AVL x);
static int getBalance(AVL N);
static AVL atualiza_avl(AVL node, void* estrutura);


AVL initAVL() {
    return NULL;
}

/* Função que devolve a altura de um dado nodo de uma AVL */

static int height(AVL n) {
    if (n == NULL)
        return 0;
    return n->height;
}


/* Função que determina o maximo entre dois valores */

static int max(int a, int b) {
    return (a > b)? a : b;
}


/* Função responsavel pela criação de um novo nodo */

static AVL newNode(Valor info, void *estrutura) {
    struct nodeAVL* node = (struct nodeAVL*) malloc(sizeof(struct nodeAVL));
    node->string = malloc(32);
    strcpy(node->string,info);
    node->cont = estrutura;
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

AVL avl_insert(AVL node, Valor info, Estrutura estrutura) {

    if (node == NULL)
        return(newNode(info,estrutura));
 
    if (strcmp(info,node->string) < 0)
        node->left  = avl_insert(node->left, info, estrutura);
    else if(strcmp(info,node->string) > 0)
        node->right = avl_insert(node->right, info, estrutura);
    else node = atualiza_avl(node,estrutura);
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

Boolean avl_lookUp(AVL node, Valor value) {
    int r;
    if(node == NULL) return false;
    else {
        r = strcmp(value,node->string);
        if(r == 0) return true;
        else if(r < 0) avl_lookUp(node->left, value);
        else avl_lookUp(node->right,value);
    }
}

int avl_count(AVL node) {
    int total;  
    
    if (node == NULL) return(0);

    total = 1 + avl_count(node->left) + avl_count(node->right);

    return total;   
}

void avl_free(AVL node) {
    if(node != NULL) {
        avl_free(node->left);
        avl_free(node->right);
        free(node);
    }
}


AVL avl_clone(AVL node) {
    
    AVL nova = avl_insert(nova,node->string, NULL);
    nova->left = avl_clone(node->left);
    nova->right = avl_clone(node->right);

    return nova;
}

void* avl_getEstrutura(AVL node, Valor value) {
    int r;
    if(node == NULL) return NULL;
    else {
        r = strcmp(value,node->string);
        if(r == 0) return node->cont;
        else if(r < 0) avl_getEstrutura(node->left, value);
        else avl_getEstrutura(node->right,value);
    }
}

static AVL atualiza_avl(AVL node, void* estrutura) {
    node->cont = estrutura;
    return node;
}