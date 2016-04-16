#include "./headers/avl.h"

/*******
Estruturas
*******/

typedef struct nodeAVL {
    Valor string;
    void *cont;
    struct nodeAVL *left;
    struct nodeAVL *right;
    int height;
} *NODO;


struct avl {
    NODO arvore;
    int avl_tamanho; 
};


struct lista {
    char** array;
    int pos;
    int capacidade;
};


/************
FUNCOES OCULTAS AO UTILIZADOR
************/

static int height(NODO n);
static int max(int a, int b);
static NODO newNode(Valor info, void *estrutura);
static NODO rightRotate(NODO y);
static NODO leftRotate(NODO x);
static int getBalance(NODO N);
static NODO atualiza_avl(NODO node, void* estrutura);
static NODO node_insert(NODO node, Valor string, Estrutura estrutura);
static Boolean node_lookUp(NODO node, Valor value);
static NODO tree_clone(NODO node);
static void tree_free(NODO node);
static Estrutura node_getEstrutura(NODO node, Valor value);


static Lista converte_aux(Lista list, NODO tree);
static Lista produtos_nao_comprados_totais_aux(Lista list, NODO tree);
static Lista clientes_compraram_filial_aux(Lista list, NODO tree);


AVL initAVL() {
    AVL tree = malloc(sizeof(struct avl));
    tree->arvore = NULL;
    tree->avl_tamanho = 0;
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


Estrutura avl_getFirst(AVL node){
    return node->arvore->cont;
}

Estrutura node_esquerdo(NODO node){
    return node->right;
}

Estrutura node_direito(NODO node){
    return node->left->cont;
}

void avl_free(AVL nodo) {
    tree_free(nodo->arvore);
    free(nodo);
}


/** 
 * Função que devolve a altura de um dado nodo de uma AVL.
 * @param n NODO de onde será devolvida a sua altura.
 * @return int com a altura do nodo.
*/
static int height(NODO n) {
    if (n == NULL)
        return 0;
    return n->height;
}

/** 
 *Função que determina o maximo entre dois valores.
 * @param a int para comparação.
 * @param b int para comparação. 
 * @return int com o maior valor.
*/
static int max(int a, int b) {
    return (a > b)? a : b;
}


/** 
 * Função responsável por alocar um novo nodo.
 * @param info char* com o valor a inserir no nodo.
 * @param estrutura void* apontador. 
 * @return node novo NODO criado.
*/
static NODO newNode(Valor info, void *estrutura) {
    struct nodeAVL* node = (struct nodeAVL*) malloc(sizeof(struct nodeAVL));
    node->string = malloc(32);
    strcpy(node->string,info);
    node->cont = estrutura;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}


static NODO rightRotate(NODO y) {

    NODO x = y->left;
    NODO T2 = x->right;
    
    /* Rotações */

    x->right = y;
    y->left = T2;
    
    /* Atualização dos pesos dos nodos */

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}


static NODO leftRotate(NODO x) {

    NODO y = x->right;
    NODO T2 = y->left;
 
    /* Rotações */

    y->left = x;
    x->right = T2;
 
    /* Atualização dos pesos dos nodos */

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    return y;
}


/* Retorna o balanceamento da arvore, estando a arvore balanceada para valores retornados entre -1 e 1 */

static int getBalance(NODO N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
/* Função com o objetivo de inserir uma nova informação na arvore */

static NODO node_insert(NODO node, Valor info, Estrutura estrutura) {
    int balance;
    if (node == NULL)
        return(newNode(info,estrutura));
 
    if (strcmp(info,node->string) < 0)
        node->left  = node_insert(node->left, info, estrutura);
    else if(strcmp(info,node->string) > 0)
        node->right = node_insert(node->right, info, estrutura);
    else node = atualiza_avl(node,estrutura);
    /* Atualiza os pesos */
    node->height = max(height(node->left), height(node->right)) + 1;
 
    /* Varifica o balanceamento */
    balance = getBalance(node);
 
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
    
    NODO aux = malloc(sizeof(struct nodeAVL));
        
    if(node) {
        aux->string = malloc(32);
        strcpy(aux->string,node->string); 
        aux->height = node->height;
        aux->cont = NULL;
        aux->left = tree_clone(node->left);
        aux->right = tree_clone(node->right);
    }
    else aux = NULL;

    return aux;
}


static NODO atualiza_avl(NODO node, Estrutura estrutura) {
    node->cont = estrutura;
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


/************************************

FUNCOES SOBRE O ARRAY DINAMICO


*************************************/

/**
 * Inicia um novo array dinâmico.
 * @param size inteiro que determina a capacidade inicial do array dinâmico.
 * @return conjunto array dinâmico
 */
Lista init_Lista(int size) {
    Lista conjunto = (Lista) malloc(sizeof(struct lista));
    conjunto->array = (char**) malloc(size *sizeof(char*));
    conjunto->pos = 0;
    conjunto->capacidade = size;
    return conjunto;
}


Lista lista_insert(Lista conjunto ,char* valor) {
    
    int posicao = conjunto->pos;
    
    if(conjunto->pos == (conjunto->capacidade - 1)) {
        conjunto->capacidade *= 2;
        conjunto->array = realloc(conjunto->array,conjunto->capacidade *sizeof(char *));
    }


    conjunto->array[posicao] = malloc(10);
    strcpy(conjunto->array[posicao],valor);
    
    conjunto->pos++;

    return conjunto;
}


Lista lista_converte(Lista list, AVL tree) {
    list = converte_aux(list,tree->arvore);
    return list;
}

static Lista converte_aux(Lista list, NODO tree) {
    if(tree != NULL) {
        list = converte_aux(list,tree->left);
        list = lista_insert(list,tree->string);
        list = converte_aux(list,tree->right);   
    }
    return list;
}


Lista produtos_nao_comprados_totais(Lista list,AVL tree) {
    list = produtos_nao_comprados_totais_aux(list,tree->arvore);
    return list;
}

static Lista produtos_nao_comprados_totais_aux(Lista list, NODO tree) {
    if(tree!=NULL) {
        list = produtos_nao_comprados_totais_aux(list,tree->left);
        if(tree->cont == NULL) list = lista_insert(list,tree->string);
        list = produtos_nao_comprados_totais_aux(list,tree->right);  
    }
    return list;
}


int lista_getPos(Lista list) {
    return list->pos;
}


char* lista_getNome(Lista list, int pos) {
    char* novo = malloc(strlen(list->array[pos])+1);
    strcpy(novo,list->array[pos]);
    return novo;
}




Lista clientes_compraram_filial(Lista list,AVL tree) {
    list = clientes_compraram_filial_aux(list,tree->arvore);
    return list;
}

static Lista clientes_compraram_filial_aux(Lista list, NODO tree) {
    if(tree!=NULL) {
        list = clientes_compraram_filial_aux(list,tree->left);
        if(tree->cont != NULL) list = lista_insert(list,tree->string);
        list = clientes_compraram_filial_aux(list,tree->right);  
    }
    return list;
}