#include "filiais.h"

#define LETRAS 26
/* Tuplo com os dois tipos de informaçoes, organizadas por produtos e por clientes */

struct info{
    AVL clientes;
    AVL produtos;
};


/*Estrutura que começa por ordenar os clientes e cria para cada um uma lista de produtos */

struct Clientes {
   AVL indice[LETRAS];
};

struct ClientesNode {
    long Total[3];
    void *nome;
    struct ClientesNode *left;
    struct ClientesNode *right;
    int height;
    AVL Produto_Cliente[12];
};

/*Lista de produtos */

struct Produto_Cliente_Node {
    void *produto;
    struct info_final *info;
    struct nodeAVL *left;
    struct nodeAVL *right;
    int height;
};


/*Estrutura que começa por ordenar os produtos e cria para cada um uma lista de clientes */

struct Produtos {
   AVL indice[LETRAS];
};

struct ProdutosNode {
    void *nome;
    long totalC[3];
    long totalU[3];
    struct nodeAVL *left;
    struct nodeAVL *right;
    int height;
    AVL Clientes_Produto[3];
};

/*Lista de clientes */

struct Clientes_Produto_Node {
    void *cliente;
    struct info_final *info;
    struct nodeAVL *left;
    struct nodeAVL *right;
    int height;
};

/* informaçao comun as duas estruturas */


struct info_final{
    long quantidade_p, quantidade_n;
    long preco_n, preco_p;
};



INFO_FILIAL init_info_filial() {

    INFO_FILIAL inf = (struct info*) malloc(sizeof(struct info));
    inf->clientes=0;
    inf->produtos=0;

    return inf;

}


char *getCompraProd(Compra compra){
    int i;

    char *new;

    for(i=0;i!=6;i++)new[i]=compra[i];

    return new;
}


float getPreco(Compra compra){
    int i,j;

    for(i=0,j=0;i!=1;j++)
        if(compra[j]==' ') i++;

    char new[6];
    j++;
    for(i=j;i!=j+5;i++)new[i]=compra[i];

    new[i]='\0';
    float price=atof(new);

    return price;
}


int getQuantidade(Compra compra){
    int i,j;

    for(i=0,j=0;i!=2;j++)
        if(compra[j]==' ') i++;

    char new[6];
    j++;
    for(i=j;i!=5;i++)new[i]=compra[i];

    new[i]='\0';
    int quant=atoi(new);

    return quant;
}



char getTipo(Compra compra){
    int i,j;

    for(i=0,j=0;j!=3;j++)
        if(compra[j]==' ') i++;

    char new;
    j++;
    new=compra[i];

    return new;
}

char *getCliente(Compra compra){
    int i,j;

    for(i=0,j=0;i!=4;j++)
        if(compra[j]==' ') i++;

    char *new;
    j++;
    for(i=j;i!=j+5;i++)new[i]=compra[i];

    return new;
}

int getMes(Compra compra){
    int i,j;

    for(i=0,j=0;i!=5;j++)
        if(compra[j]==' ') i++;

    char new[3];
    j++;
    for(i=j;i!=j+2;i++)new[i]=compra[i];

    new[i]='\0';
    int mes=atoi(new);

    return mes;
}


int getFilial(Compra compra){
    int new;
    int i,j;

    for(i=0,j=0;i!=6;j++)
        if(compra[j]==' ') i++;
    j++;
    new=compra[j]-'0';

    return new;
}


INFO_FILIAL insere_compra(INFO_FILIAL inf, Compra compra) {
    char *new;
    int index;
    new=getCompraProd(compra);
    index = new[0]-'A';
    /*inf->produtos->indice[index] = compra_prod_insert(inf->produtos->indice[index], compra, NULL); */

    new=getCliente(compra);
    index= new[0]-'A';
    /*inf->clientes->indice[index] = compra_prod_insert(inf->clientes->indice[index], compra, NULL); */

    return inf;
}



/*

Função responsavel pela criação de um novo nodo 

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


AVL avl_insert(AVL node, Valor info, void *estrutura) {

    if (node == NULL)
        return(newNode(info,estrutura));
 
    if (strcmp(info,node->string) < 0)
        node->left  = avl_insert(node->left, info, estrutura);
    else
        node->right = avl_insert(node->right, info, estrutura);
 
    /* Atualiza os pesos 
    node->height = max(height(node->left), height(node->right)) + 1;
 
    /* Varifica o balanceamento 
    int balance = getBalance(node);
 
    /* Left Left Case 
    if (balance > 1 && strcmp(info,node->left->string) < 0)
        return rightRotate(node);
 
    /* Right Right Case 
    if (balance < -1 && strcmp(info,node->right->string) > 0)
        return leftRotate(node);
 
    /* Left Right Case 
    if (balance > 1 && strcmp(info,node->left->string) > 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
     /* Right Left Case 
    if (balance < -1 && strcmp(info, node->right->string) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}

*/

