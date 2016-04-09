#include "./headers/avl.h"

/*******
Estruturas
*******/

struct nodeAVL {
    Valor string;
    void *cont;
    struct nodeAVL *left;
    struct nodeAVL *right;
    int height;
};

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
static Lista lista_insert(Lista conjunto ,char* valor);


/******
FUNCOES DE AVL'S
*******/


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

void avl_free(AVL nodo) {
    tree_free(nodo->arvore);
    free(nodo);
}

/***********
FUNCOES QUE TRABALHAM COM UM "NODO"
***********/


/* Função que devolve a altura de um dado nodo de uma AVL */

static int height(NODO n) {
    if (n == NULL)
        return 0;
    return n->height;
}


/* Função que determina o maximo entre dois valores */

static int max(int a, int b) {
    return (a > b)? a : b;
}


/* Função responsavel pela criação de um novo nodo */

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
        aux->cont = node->cont;
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



/************
FUNCOES RELATIVAS AOS ARRAYS DINAMICOS
********/

Lista init_Lista(int size) {
    Lista conjunto = (Lista) malloc(sizeof(struct lista));
    conjunto->array = (char**) malloc(size *sizeof(char*));
    conjunto->pos = 0;
    conjunto->capacidade = size;
    return conjunto;
}

static Lista lista_insert(Lista conjunto ,char* valor) {
    
    int posicao = conjunto->pos;
    
    if(conjunto->pos == (conjunto->capacidade - 1)) {
        conjunto->capacidade *= 2;
        conjunto->array = realloc(conjunto->array,conjunto->capacidade *sizeof(char *));
    }


    conjunto->array[posicao] = malloc(10);
    strncpy(conjunto->array[posicao],valor,strlen(valor));
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

void apresenta_Lista(Lista list) {
    int i;
    int estado = 1;
    int nr_de_elementos = list->pos + 1;

    if(nr_de_elementos == 0) estado = 0;
    
    int elementos_pagina = 20;
    
    
    int last_pagina = nr_de_elementos % elementos_pagina;
    
    int total_paginas = (last_pagina == 0) ? (nr_de_elementos / elementos_pagina) : ((nr_de_elementos / elementos_pagina) + 1); 

    int nr_pagina = 1;

    while(estado) {
        
        printf(" --- Página número |%d| de |%d| ---\n", nr_pagina,total_paginas);
        

        for(i = (nr_pagina-1) * elementos_pagina; i < (nr_pagina * elementos_pagina) && i < nr_de_elementos-1; i++) {
            printf("\t%d\t%s\n",i+1,list->array[i]);
        }

        putchar('\n');
        printf(" 1 - [<<]  2 - [<]  3 - [>]  4 - [>>]   0 - Sair\n");
        putchar('\n');
        printf("Opcao numero > ");
        scanf("%d",&estado);
        printf("ESTADO: %d\n",estado);
        
        switch(estado) {
            case 0: break;
            case 1: nr_pagina = 1;

            case 2: if(nr_pagina > 1) nr_pagina --;
                   break;
            case 3: if(nr_pagina < total_paginas) nr_pagina++;
                   break;
            case 4: nr_pagina = total_paginas;
            default:printf("Opção não valida\n"); 
                    break;
        }

    }
}