#include "filiais.h"

#define NR_LETRAS 26
#define MESES 12
#define FILIAIS 3
/* Tuplo com os dois tipos de informaçoes, organizadas por produtos e por clientes */

struct info{
    struct catalogo *clientes;
    struct catalogo *produtos;
};


/*Estrutura que começa por ordenar os clientes e cria para cada um uma lista de produtos */

struct ClientesNode{
    long Total[FILIAIS];
    void *nome;
    struct catalogo *Produto_Cliente;
    /*catalogo tamanho MESES*/
};

/*Lista de produtos */

struct Produto_Cliente_Node{
    void *produto;
    struct info_final *info;
};

/*Estrutura que começa por ordenar os produtos e cria para cada um uma lista de clientes */

struct ProdutosNode{
    void *nome;
    long totalU[FILIAIS];
    long totalC[FILIAIS];
    struct catalogo* Clientes_Produto;
    /*catalogo tamanho FILIAIS*/
};

/*Lista de clientes */

struct Clientes_Produto_Node {
    void *cliente;
    struct info_final *info;
};

/* informaçao comun as duas estruturas */

struct info_final{
    long quantidade_p, quantidade_n;
    long preco_n, preco_p;
};



struct info *init_info_filial() {

    int i;
    struct info *inf = (struct info*) malloc(sizeof(struct info));
    struct catalogo* produtos=init_Catalogo(NR_LETRAS);
    struct catalogo* clientes=init_Catalogo(NR_LETRAS);

    inf->clientes=clientes;
    inf->produtos=produtos;

    return inf;

}

struct ProdutosNode *init_infoprod(Compra compra){

    int i;
    struct ProdutosNode* node = (struct ProdutosNode*) malloc(sizeof(struct ProdutosNode));
    node->nome=NULL;
    for(i=0;i!=FILIAIS;i++){
        node->totalU[i]=0;
        node->totalC[i]=0;
    }

    struct catalogo* clientes=init_Catalogo(FILIAIS);    
    node->Clientes_Produto=clientes;

    return node;

}





struct info *full_init(){

        
        struct info *a=init_info_filial();
        AVL prod= initAVL();
        AVL cli= initAVL();
        /*init_infoprod()*/
        AVL cliToProd=initAVL();
        /*init_infoCliInProd*/
        /*init_info_last*/

        /*init_infocli*/
        AVL prodToCli= initAVL();
        /*init_infoProdInCli*/
        /*init_infolast*/


    return a;
}


struct info *insere_compra(struct info *inf, Compra compra) {
    char *new;
    int index;
    new=getProd(compra);
    index = new[0]-'A';
    if(inf==NULL) inf=full_init();
    

    /*FAZER UMA INSERE AQUI*/



    new=getCli(compra);
    index= new[0]-'A';
    if(inf==NULL) inf=full_init();
     


    /*FAZER UMA INSERE AQUI*/


    return inf;
}




