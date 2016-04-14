#include "./headers/filiais.h"

#define NR_LETRAS 26
#define MESES 12
#define FILIAIS 3
/* Tuplo com os dois tipos de informaçoes, organizadas por produtos e por clientes */

struct conjunto_filiais {
  Array lista;
};



struct info{
    Catalogo clientes;
    Catalogo produtos;
};


/*Estrutura que começa por ordenar os clientes e cria para cada um uma lista de produtos */

struct clientesNode{
    Catalogo Produtos_Cliente;
    int total[12][3];
    /*array meses, filiais*/
    /*catalogo tamanho MESES*/
};


/*Estrutura que começa por ordenar os produtos e cria para cada um uma lista de clientes */

struct produtosNode{
    long totalU[FILIAIS];
    long totalCN[FILIAIS];
    long totalCP[FILIAIS];
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
        node->totalCN[i]=0;
        node->totalCP[i]=0;
    }

    node->Clientes_Produto=init_Catalogo(FILIAIS);    
    
    return node;

}

ClientesNode init_infocli(){

    int i,j;
    ClientesNode node = (ClientesNode) malloc(sizeof(struct clientesNode));
    for(j=0;j!=MESES;j++){
        for(i=0;i!=FILIAIS;i++){
            node->total[j][i]=0;
        }
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



INFO_FILIAL insere_produto_estrutura(INFO_FILIAL inf, Venda sale,Info_Final final,ProdutosNode node){ 
    char *indexp = getNomeProduto(getProduto(sale));
    char *indexc = getNomeCliente(getCliente(sale));
    
    if(node==NULL) node=init_infoprod();
    node->totalU[getFilial(sale)-1]+=getQuantidade(sale);
    if(getPromocao(sale)=='N') node->totalCN[getFilial(sale)-1]++;
    else node->totalCP[getFilial(sale)-1]++;
    node->Clientes_Produto=insere_Catalogo(node->Clientes_Produto,indexc,final,getFilial(sale)-1);
    inf->produtos=insere_Catalogo(inf->produtos,indexp,node,indexp[0]-'A');

    return inf;
}

INFO_FILIAL insere_cliente_estrutura(INFO_FILIAL inf, Venda sale,Info_Final final,ClientesNode node){
    char *indexp = getNomeProduto(getProduto(sale));
    char *indexc = getNomeCliente(getCliente(sale));

    if(node==NULL) node=init_infocli(); 
    node->total[getMes(sale)-1][getFilial(sale)-1]+=getQuantidade(sale);
    node->Produtos_Cliente=insere_Catalogo(node->Produtos_Cliente,indexp,final,getMes(sale)-1);
    inf->clientes=insere_Catalogo(inf->clientes,indexc,node,indexc[0]-'A');

    return inf;
}


Info_Final insere_final_estrutura(INFO_FILIAL inf, Venda sale,ClientesNode nodecli,ProdutosNode nodepro){
    char *indexp = getNomeProduto(getProduto(sale));
    Info_Final last =init_infolast(sale);
        
        if(nodepro!=NULL && nodecli!=NULL){
        /*Produto existe*/
        if(nodecli->Produtos_Cliente!=NULL){
        last=getEstrutura_Catalogo(nodecli->Produtos_Cliente,indexp,getMes(sale)-1);
        last=update_infolast(sale,last);
        }
    }
    return last;
}





INFO_FILIAL insere_compra(INFO_FILIAL inf,Venda sale) {
    char *indexp = getNomeProduto(getProduto(sale));
    char *indexc = getNomeCliente(getCliente(sale));
    ProdutosNode nodepro = getEstrutura_Catalogo(inf->produtos,indexp,indexp[0]-'A');
    ClientesNode nodecli = getEstrutura_Catalogo(inf->produtos,indexc,indexc[0]-'A');
    Info_Final final =insere_final_estrutura(inf,sale,nodecli,nodepro);
    inf=insere_produto_estrutura(inf,sale,final,nodepro);
    inf=insere_cliente_estrutura(inf,sale,final,nodecli);
    return inf;
}

int getprodutosComprados(INFO_FILIAL info,char *cliente,int mes,int filiais){
    int i,j;
    ClientesNode node =getEstrutura_Catalogo(info->clientes,cliente, cliente[0]-'A');
    if(node==NULL) return -1;
    return node->total[mes][filiais];    
}


Boolean info_lookUp(INFO_FILIAL info,char *string,int n){
    if (n==0) return existe_Catalogo(info->produtos,string,string[0]-'A');
    else return existe_Catalogo(info->clientes,string,string[0]-'A');
}

int getnotprodutos(INFO_FILIAL info,int lim){
    int n=0;
    n=percorrercat(info->produtos,lim,0);

    return n;
}


int getnotclientes(INFO_FILIAL info,int lim){
    int n=0;
    n=percorrercat(info->clientes,lim,1);

    return n;
}

Boolean nexisteproduto(ProdutosNode pro){
    return (pro->totalU[0]==0 && pro->totalU[1]==0 && pro->totalU[2]==0);
}

Boolean nexistecliente(ClientesNode cli){
    int i,j;
    for(i=0;i!=MESES;i++)
        for(j=0;j!=FILIAIS;j++)
            if(cli->total[j][i]!=0) return false;
    return true;
}
