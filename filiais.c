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

struct clientesNode{
    long total[FILIAIS];
    struct catalogo *Produto_Cliente;
    /*catalogo tamanho MESES*/
};

/*Lista de produtos */

struct produtos_Cliente_Node{
    struct info_final *info;
};

/*Estrutura que começa por ordenar os produtos e cria para cada um uma lista de clientes */

struct produtosNode{
    long totalU[FILIAIS];
    long totalC[FILIAIS];
    struct catalogo* Clientes_Produto;
    /*catalogo tamanho FILIAIS*/
};

/*Lista de clientes */

struct clientes_Produto_Node {
    struct info_final *info;
};

/* informaçao comun as duas estruturas */

struct info_final{
    long quantidade_p, quantidade_n;
    long preco_n, preco_p;
};



INFO_FILIAL init_info_filial() {

    int i;
    INFO_FILIAL inf = (INFO_FILIAL) malloc(sizeof(struct info));
    Catalogo produtos=init_Catalogo(NR_LETRAS);
    Catalogo clientes=init_Catalogo(NR_LETRAS);

    inf->clientes=clientes;
    inf->produtos=produtos;

    return inf;

}

ProdutosNode init_infoprod(){

    int i;
    ProdutosNode node = (ProdutosNode) malloc(sizeof(struct produtosNode));
    for(i=0;i!=FILIAIS;i++){
        node->totalU[i]=0;
        node->totalC[i]=0;
    }

    Catalogo clientes=init_Catalogo(FILIAIS);    
    node->Clientes_Produto=clientes;

    return node;

}

ClientesNode init_infocli(){

    int i;
    ClientesNode node = (ClientesNode) malloc(sizeof(struct clientesNode));
    for(i=0;i!=FILIAIS;i++){
        node->total[i]=0;
    }

    Catalogo produtos=init_Catalogo(MESES);    
    node->Produto_Cliente=produtos;

    return node;

}


Clientes_Produto_Node init_infoCliInProd(){
    Clientes_Produto_Node clipro = (Clientes_Produto_Node) malloc(sizeof(struct clientes_Produto_Node));
    return clipro;
}

Produtos_Cliente_Node init_infoProdInCli(){
    Produtos_Cliente_Node procli = (Produtos_Cliente_Node) malloc(sizeof(struct produtos_Cliente_Node));
    return procli;
}


Info_Final init_infolast(Venda sale){
    Info_Final final = (Info_Final) malloc(sizeof(struct info_final));
    if(getPromocao(sale)=='N'){
        final->quantidade_n=getQuantidade(sale);
        final->quantidade_p=0;
        final->preco_n=getPreco(sale)*getQuantidade(sale);
        final->preco_p=0;}
    else{
        final->quantidade_n=0;
        final->quantidade_p=getQuantidade(sale);
        final->preco_n=0;
        final->preco_p=getPreco(sale)*getQuantidade(sale);}


    return final;

}






INFO_FILIAL full_init(Venda  sale){

        
    INFO_FILIAL Estrutura_Geral=init_info_filial();
    Catalogo Catalogo_Clientes =init_Catalogo(NR_LETRAS);
    Catalogo Catalogo_Produtos =init_Catalogo(NR_LETRAS);
    ProdutosNode Informacao_Produtos_Inicial=init_infoprod();
    Produtos_Cliente_Node ProdutosDosClientes= init_infoProdInCli();
    ClientesNode Informacao_Clientes_Inicial=init_infocli();       
    Clientes_Produto_Node ClientesDosProdutos= init_infoCliInProd();
    Info_Final final=init_infolast(sale);

    ProdutosDosClientes->info=final;
    ClientesDosProdutos->info=final;

    char indice;
    indice='A'+getNomeCliente(getCliente(sale))[0]; 
    Catalogo_Clientes=insere_Catalogo(Catalogo_Clientes,getNomeCliente(getCliente(sale)),Informacao_Clientes_Inicial);
    indice='A'+getNomeProduto(getProduto(sale))[0];
    Catalogo_Produtos=insere_Catalogo(Catalogo_Produtos,getNomeProduto(getProduto(sale)),Informacao_Produtos_Inicial);


    Estrutura_Geral->clientes=Catalogo_Clientes;
    Estrutura_Geral->produtos=Catalogo_Produtos;

    return Estrutura_Geral;
}



Info_Final update_infolast(Venda sale){
    Info_Final final = (Info_Final) malloc(sizeof(struct info_final));
    if(getPromocao(sale)=='N'){
                /*Preço Normal*/
                final->quantidade_n+=getQuantidade(sale);
                final->preco_n+=getPreco(sale);
                }
            else{
                /*Promoção*/
                final->quantidade_p+=getQuantidade(sale);
                final->preco_p+=getPreco(sale);
            }


    return final;

}







INFO_FILIAL insere_compra(INFO_FILIAL inf,Venda sale) {

    int index,i;
    index = getNomeProduto(getProduto(sale))[0]-'A';

    if(avl_lookup(inf->produtos,getNomeProduto(getProduto(sale)))){
        /*Produto existe*/
        index=getNomeProduto(getProduto(sale))[0]-'A';
        ProdutosNode node =avl_getEstrutura(inf->produtos->indice[index],getNomeProduto(getProduto(sale)));
        node->totalU[getFILIAL(sale)]+=getQuantidade(sale);
        if(avl_lookup(node->Clientes_Produto,getNomeCliente(getCliente(sale)))){
            /*Cliente existe*/
            Clientes_Produto_Node nodeAux=avl_getEstrutura(node->Clientes_Produto->indice[getNomeCliente(getCliente(sale))],getNomeCliente(getCliente(sale)));
            nodeAux->info=update_infolast(sale);
        }
        else{
            /*Cliente novo*/
            node->totalC[getFILIAL(sale)]++;
            Info_Final last =init_infolast(sale);
            avl_insert(node->Clientes_Produto->indice[getFILIAL(sale)],getNomeCliente(getCliente(sale)),last);
            }    
        }
    
    else{
        /*Produto Novo*/
        ProdutosNode node=init_infoprod();
        inf->produtos->indice[getNomeProduto(getProduto(sale))[0]-'A']->string=getNomeProduto(getProduto(sale));
        node->totalU[getFILIAL(sale)]+=getQuantidade(sale);
        

        node->totalC[getFILIAL(sale)]++;
        Info_Final last =init_infolast(sale);
        avl_insert(node->Clientes_Produto->indice[getNomeCliente(getCliente(sale))],getNomeCliente(getCliente(sale)),last);


        Clientes_Produto_Node nodeAux=avl_getEstrutura(node->Clientes_Produto->indice[getNomeCliente(getCliente(sale))],getNomeCliente(getCliente(sale)));
        nodeAux->info=update_infolast(sale);
    }
        

    index= getNomeCliente(getCliente(sale))[0]-'A';
    
    return inf;
}




