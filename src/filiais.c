#include "./headers/filiais.h"

#define NR_LETRAS 26
#define MESES 12
#define FILIAIS 3
/* Tuplo com os dois tipos de informaçoes, organizadas por produtos e por clientes */

struct info{
    Catalogo clientes;
    Catalogo produtos;
};


/*Estrutura que começa por ordenar os clientes e cria para cada um uma lista de produtos */

struct clientesNode{
    float total[FILIAIS];
    Catalogo Produtos_Cliente;
    /*catalogo tamanho MESES*/
};


/*Estrutura que começa por ordenar os produtos e cria para cada um uma lista de clientes */

struct produtosNode{
    long totalU[FILIAIS];
    long totalC[FILIAIS];
    Catalogo Clientes_Produto;
    /*catalogo tamanho FILIAIS*/
};



/* informaçao comun as duas estruturas */

struct info_final{
    long quantidade_p, quantidade_n;
    long preco_n, preco_p;
};



INFO_FILIAL init_info_filial(INFO_FILIAL inf, Cat_Produtos produtos, Cat_Clientes clientes) {
    inf->produtos=clone_Catalogo(get_Catalogo(produtos));
    inf->clientes=clone_Catalogo(get_CatalogoCli(clientes));

    return inf;

}


ProdutosNode init_infoprod(){

    int i;
    ProdutosNode node = (ProdutosNode) malloc(sizeof(struct produtosNode));
    for(i=0;i!=FILIAIS;i++){
        node->totalU[i]=0;
        node->totalC[i]=0;
    }

    node->Clientes_Produto=init_Catalogo(FILIAIS);    
    
    return node;

}

ClientesNode init_infocli(){

    int i;
    ClientesNode node = (ClientesNode) malloc(sizeof(struct clientesNode));
    for(i=0;i!=FILIAIS;i++){
        node->total[i]=0;
    }

    node->Produtos_Cliente=init_Catalogo(MESES);
    return node;

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


INFO_FILIAL init_filiais(){
    INFO_FILIAL info = (INFO_FILIAL) malloc(sizeof(struct info));
    info->produtos=NULL;
    info->clientes=NULL;
    return info;
}

INFO_FILIAL full_init(INFO_FILIAL info, Cat_Produtos produtos, Cat_Clientes clientes){
    INFO_FILIAL Estrutura_Geral=init_info_filial(info, produtos, clientes);
    return Estrutura_Geral;
}



Info_Final update_infolast(Venda sale, Info_Final final){
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



INFO_FILIAL insere_produto_estrutura(INFO_FILIAL inf, Venda sale){ 
    char * indexp;
    char * indexc;
    int i;
    indexp = getNomeProduto(getProduto(sale));
    indexc = getNomeCliente(getCliente(sale));

    
    ProdutosNode node =getEstrutura_Catalogo(inf->produtos,indexp,indexp[0]-'A');
    if(node==NULL) node=init_infoprod();
    node->totalU[getFilial(sale)]+=getQuantidade(sale);
    insere_Catalogo(inf->produtos,getNomeProduto(getProduto(sale)),node,indexp[0]-'A');
    if(existe_Catalogo(node->Clientes_Produto,indexc)){
        /*Cliente existe*/
        Info_Final final=getEstrutura_Catalogo(node->Clientes_Produto,indexc,getFilial(sale)-1);
        final=update_infolast(sale,final);
        insere_Catalogo(node->Clientes_Produto,getNomeProduto(getProduto(sale)),final,getFilial(sale)-1);
    }
    else{
        /*Cliente novo*/
        node->totalC[getFilial(sale)-1]++;
        Info_Final last =init_infolast(sale);
        insere_Catalogo(node->Clientes_Produto,getNomeProduto(getProduto(sale)),last,getFilial(sale)-1);
        }    
    
    
    
    return inf;
}

INFO_FILIAL insere_cliente_estrutura(INFO_FILIAL inf, Venda sale){
    char * indexp;
    char * indexc;
    int i;
    indexp = getNomeProduto(getProduto(sale));
    indexc = getNomeCliente(getCliente(sale));

   
    ClientesNode node =getEstrutura_Catalogo(inf->produtos,getNomeCliente(getCliente(sale)),indexp[0]-'A');
    if(node==NULL) node=init_infocli();
    node->total[getFilial(sale)]+=getQuantidade(sale)*getPreco(sale);
    insere_Catalogo(inf->clientes,getNomeCliente(getCliente(sale)),node,indexc[0]-'A');
    if(existe_Catalogo(node->Produtos_Cliente,getNomeProduto(getProduto(sale)))){
        /*Produto existe*/
        Info_Final final=getEstrutura_Catalogo(node->Produtos_Cliente,getNomeProduto(getProduto(sale)),getMes(sale)-1);
        final=update_infolast(sale,final);
        insere_Catalogo(node->Produtos_Cliente,getNomeCliente(getCliente(sale)),final,getMes(sale)-1);
    }
    else{
        /*Produto novo*/
        node->total[getFilial(sale)]+=getQuantidade(sale)*getPreco(sale);
        Info_Final last =init_infolast(sale);
        insere_Catalogo(node->Produtos_Cliente,getNomeCliente(getCliente(sale)),last,getMes(sale)-1);
       
        }    
    
    return inf;
}






INFO_FILIAL insere_compra(INFO_FILIAL inf,Venda sale) {
    int index,i;
    inf=insere_produto_estrutura(inf,sale);
    inf=insere_cliente_estrutura(inf,sale);
    return inf;
}




