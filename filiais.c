#include "filiais.h"

#define LETRAS 26
#define MESES 12
#define FILIAIS 3
/* Tuplo com os dois tipos de informaçoes, organizadas por produtos e por clientes */

struct info{
    struct catalogo *clientes;
    struct catalogo *produtos;
};

struct catalogo {
   AVL indice[26];
};


/*Estrutura que começa por ordenar os clientes e cria para cada um uma lista de produtos */

struct ClientesNode{
    long Total[FILIAIS];
    void *nome;
    AVL Produto_Cliente[MESES];
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
    AVL Clientes_Produto[FILIAIS];
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



INFO_FILIAL init_info_filial() {

    int i;
    INFO_FILIAL inf = (struct info*) malloc(sizeof(struct info));
    struct catalogo* catc=(struct catalogo*) malloc(sizeof(struct catalogo));
    struct catalogo* catp=(struct catalogo*) malloc(sizeof(struct catalogo));
    for(i=0;i!=LETRAS;i++){
        catc->indice[i]=NULL;
        catc->indice[i]=NULL;
    }

    inf->clientes=catc;
    inf->produtos=catp;

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





INFO_FILIAL *init_inf(){
    int i;
    INFO_FILIAL inf = (struct info*) malloc(sizeof(struct info));
    struct catalogo* catc=(struct catalogo*) malloc(sizeof(struct catalogo));
    struct catalogo* catp=(struct catalogo*) malloc(sizeof(struct catalogo));

    inf->clientes=catc;
    inf->produtos=catp;

    for(i=0;i!=LETRAS;i++){
        catc[i]=NULL;
        catp[i]=NULL;
    }

    return inf;

}




AVL full_init(){

    
        /*struct info_final inf=init_info_final();
        struct Clientes_Produto_Node cpn=init_InfCliInProd();
        struct Produto_Cliente_Node  pcn=init_InfProdInCli();
        struct  init_AVLCliInProd();
        init_AVLProdInCli();
        init_InfProd();
        init_InfCLi();
        init_inf();*/
        init_AVLProd();
        init_AVLCli();
        init_catalogos();
        struct INFO_FILIAL *a =init_inf();

    return a;
}


INFO_FILIAL insere_compra(INFO_FILIAL inf, Compra compra) {
    char *new;
    int index;
    new=getCompraProd(compra);
    index = new[0]-'A';
    if(inf->produtos->indice[index]==NULL) inf->produtos->indice[index]=full_init();
    inf->produtos->indice[index] = compra_prod_insert(inf->produtos->indice[index], compra); 

    new=getCliente(compra);
    index= new[0]-'A';
    if(inf->clientes->indice[index]==NULL) inf->clientes->indice[index]=full_init();
    inf->clientes->indice[index] = compra_prod_insert(inf->clientes->indice[index], compra); 

    return inf;
}




