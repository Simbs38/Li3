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
    long total[FILIAIS];
    char *nome;
    struct catalogo *Produto_Cliente;
    /*catalogo tamanho MESES*/
};

/*Lista de produtos */

struct Produto_Cliente_Node{
    char *produto;
    struct info_final *info;
};

/*Estrutura que começa por ordenar os produtos e cria para cada um uma lista de clientes */

struct ProdutosNode{
    char *nome;
    long totalU[FILIAIS];
    long totalC[FILIAIS];
    struct catalogo* Clientes_Produto;
    /*catalogo tamanho FILIAIS*/
};

/*Lista de clientes */

struct Clientes_Produto_Node {
    char *cliente;
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

struct ProdutosNode *init_infoprod(){

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

struct ClientesNode *init_infocli(){

    int i;
    struct ClientesNode* node = (struct ClientesNode*) malloc(sizeof(struct ClientesNode));
    node->nome=NULL;
    for(i=0;i!=FILIAIS;i++){
        node->total[i]=0;
    }

    struct catalogo* produtos=init_Catalogo(MESES);    
    node->Produto_Cliente=produtos;

    return node;

}


struct Clientes_Produto_Node *init_infoCliInProd(){
    struct Clientes_Produto_Node *clipro = (struct Clientes_Produto_Node*) malloc(sizeof(struct Clientes_Produto_Node));
    clipro->cliente="NA";

    clipro->info=NULL;

    return clipro;

}

struct Produto_Cliente_Node *init_infoProdInCli(){
    struct Produto_Cliente_Node *procli = (struct Produto_Cliente_Node*) malloc(sizeof(struct Produto_Cliente_Node));
    procli->produto="NA";

    procli->info=NULL;

    return procli;

}


struct info_final *init_infolast(){
    struct info_final *final = (struct info_final *) malloc(sizeof(struct info_final));
    final->quantidade_n=0;
    final->quantidade_p=0;
    final->preco_n=0;
    final->preco_p=0;

    return final;

}






struct info *full_init(Venda  sale){

        
        /**/struct info *Estrutura_Geral=init_info_filial();

        /**/struct catalogo *Catalogo_Clientes =init_Catalogo(NR_LETRAS);
        /**/struct catalogo *Catalogo_Produtos =init_Catalogo(NR_LETRAS);

        /**/AVL AVL_Produtos_Inicial= initAVL();
        /**/AVL AVL_Clientes_Inicial= initAVL();

        /**/struct ProdutosNode *Informacao_Produtos_Inicial=init_infoprod();
        
        AVL AVL_ClientesDosProdutos=initAVL();
        struct Produto_Cliente_Node *ProdutosDosClientes= init_infoProdInCli();

        /**/struct ClientesNode *Informacao_Clientes_Inicial=init_infocli();
        
        AVL AVL_ProdutosDosClientes= initAVL();
        /**/struct Clientes_Produto_Node *ClientesDosProdutos= init_infoCliInProd();
        struct info_final *final=init_infolast();

        

        ProdutosDosClientes->info=final;
        ClientesDosProdutos->info=final;

        char indice;
        indice='A'+getMes(sale)-1;
        Informacao_Clientes_Inicial->Produto_Cliente=insere_Catalogo(Informacao_Clientes_Inicial->Produto_Cliente,&indice,AVL_ClientesDosProdutos);
        
        indice='A'+getFilial(sale)-1;
        Informacao_Produtos_Inicial->Clientes_Produto=insere_Catalogo(Informacao_Produtos_Inicial->Clientes_Produto,&indice,AVL_ProdutosDosClientes);

        avl_insert(AVL_Produtos_Inicial,getNomeProduto(getProduto(sale)),Informacao_Produtos_Inicial);
        avl_insert(AVL_Clientes_Inicial,getNomeCliente(getCliente(sale)),Informacao_Clientes_Inicial);


        indice='A'+getNomeCliente(getCliente(sale))[0]; 
        Catalogo_Clientes=insere_Catalogo(Catalogo_Clientes,&indice,AVL_Clientes_Inicial);
        indice='A'+getNomeProduto(getProduto(sale))[0];
        Catalogo_Produtos=insere_Catalogo(Catalogo_Produtos,&indice,AVL_Produtos_Inicial);


        Estrutura_Geral->clientes=Catalogo_Clientes;
        Estrutura_Geral->produtos=Catalogo_Produtos;



    return Estrutura_Geral;
}


struct info *insere_compra(struct info *inf,Venda sale) {

    int index;
    index = getNomeProduto(getProduto(sale))[0]-'A';
    if(inf==NULL) inf=full_init(sale);
    

    /*FAZER UMA INSERE AQUI*/
    /*inserir cenas em A+mes ou A+filial*/



    index= getNomeCliente(getCliente(sale))[0]-'A';
    if(inf==NULL) inf=full_init(sale);
     


    /*FAZER UMA INSERE AQUI*/


    return inf;
}




