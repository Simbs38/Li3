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



INFO_FILIAL init_info_filial() {

    int i;
    INFO_FILIAL inf = (INFO_FILIAL) malloc(sizeof(struct info));
    inf->produtos=init_Catalogo(NR_LETRAS);
    inf->clientes=init_Catalogo(NR_LETRAS);

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






INFO_FILIAL full_init(){
    INFO_FILIAL Estrutura_Geral=init_info_filial();
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

    if(existe_Catalogo(inf->produtos,getNomeProduto(getProduto(sale)))){
        /*Produto existe*/
        printf("1\n");
        ProdutosNode node =getEstrutura_Catalogo(inf->produtos,indexp,indexp[0]-'A');
        node->totalU[getFilial(sale)]+=getQuantidade(sale);
        printf("2\n");
        if(existe_Catalogo(node->Clientes_Produto,indexc)){
            /*Cliente existe*/
            printf("3\n");
            Info_Final final=getEstrutura_Catalogo(node->Clientes_Produto,indexc,getFilial(sale)-1);
            final=update_infolast(sale,final);
            printf("4\n");
        }
        else{
            /*Cliente novo*/
            printf("5\n");
            node->totalC[getFilial(sale)]++;
            Info_Final last =init_infolast(sale);
            avl_insert(getEstrutura_Catalogo(node->Clientes_Produto,indexc,getFilial(sale)),indexc,last);
            printf("6\n");
            }    
        }
    
    else{
        /*Produto Novo*/
        printf("7\n"); printf("%s\n",indexp );
        ProdutosNode node=init_infoprod();
        node->totalU[getFilial(sale)]+=getQuantidade(sale);
        insere_Catalogo(inf->produtos,indexp,node,indexp[0]-'A');
        
        
        node->totalC[getFilial(sale)]++;
        Info_Final last =init_infolast(sale);
        printf("7--\n");
        node->Clientes_Produto=insere_Catalogo(node->Clientes_Produto,getNomeCliente(getCliente(sale)),last,getFilial(sale)-1);
        
        printf("7----\n");
        Info_Final final=getEstrutura_Catalogo(node->Clientes_Produto,getNomeCliente(getCliente(sale)),getFilial(sale)-1);
        final=update_infolast(sale,final);
        printf("8\n");
    }
    printf("10\n");
    return inf;
}

INFO_FILIAL insere_cliente_estrutura(INFO_FILIAL inf, Venda sale){
    char * indexp;
    char * indexc;
    int i;
    indexp = getNomeProduto(getProduto(sale));
    indexc = getNomeCliente(getCliente(sale));

    if(existe_Catalogo(inf->produtos,getNomeCliente(getCliente(sale)))){
        /*Cliente existe*/
        printf("11\n");   
        ClientesNode node =getEstrutura_Catalogo(inf->produtos,getNomeCliente(getCliente(sale)),indexp[0]-'A');
        node->total[getFilial(sale)]+=getQuantidade(sale)*getPreco(sale);
        printf("22\n");
        if(existe_Catalogo(node->Produtos_Cliente,getNomeProduto(getProduto(sale)))){
            /*Produto existe*/
            printf("33\n");
            Info_Final final=getEstrutura_Catalogo(node->Produtos_Cliente,getNomeProduto(getProduto(sale)),getMes(sale));
            final=update_infolast(sale,final);
            printf("44\n");
        }
        else{
            /*Produto novo*/
            printf("55\n");
            node->total[getFilial(sale)]+=getQuantidade(sale)*getPreco(sale);
            Info_Final last =init_infolast(sale);
            insere_Catalogo(node->Produtos_Cliente,getNomeCliente(getCliente(sale)),last,getMes(sale));
            printf("66\n");
            }    
        }
    
    else{
        /*Cliente Novo*/
        printf("77\n");
        ClientesNode node =init_infocli();
        node->total[getFilial(sale)-1]=getPreco(sale)*getQuantidade(sale);
        insere_Catalogo(inf->clientes,indexc,node,indexc[0]-'A');

        Info_Final last =init_infolast(sale);
        node->Produtos_Cliente =insere_Catalogo(node->Produtos_Cliente,indexc,last,getMes(sale)-1);
        Produtos_Cliente_Node nodeAux=getEstrutura_Catalogo(node->Produtos_Cliente,getNomeCliente(getCliente(sale)),getMes(sale)-1);
        printf("88\n");
    }
    printf("99\n");
    return inf;
}






INFO_FILIAL insere_compra(INFO_FILIAL inf,Venda sale) {
    int index,i;
    printf("--------------%s\n",getNomeCliente(getCliente(sale)));
    inf=insere_produto_estrutura(inf,sale);
    inf=insere_cliente_estrutura(inf,sale);
    return inf;
}




