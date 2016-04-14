#include "./headers/filiais.h"


struct filial{
    Catalogo clientes;
    Catalogo produtos;
};

struct filiais {
	Filial filiais[3];
};


/*Estrutura inserida em cada nodo referente a um cliente */

struct nodo_clientes {
    Catalogo Produtos_Cliente;
    int total[12];
};

/*Estrutura inserida em cada nodo referente a um produto */

struct nodo_produtos{
	int quantidade;
	Conj_Filiais clientes_N;
	Conj_Filiais clientes_P;
};

struct conjunto_filiais {
  Array lista;
};


/*************************
	FUNCOES DE FILIAIS
**************************/

Filiais init_Filiais() {
	Filiais f = (Filiais) malloc(sizeof(struct filiais));
	int i;
	for(i = 0; i < 3; i++) {
		f->filiais[i] = init_Filial();
	}
	return f;
}

Filiais adiciona_Filiais(Filiais f, Venda v) {
	int filial = getFilial(v)-1;
	f->filiais[filial] = adiciona_Venda_Filial(f->filiais[filial],v);
	return f;
}

Filiais cria_Dados_Filiais(Filiais f,Cat_Produtos produtos,Cat_Clientes clientes) {
	int i;
	for(i = 0; i < 3; i++) {
		f->filiais[i] = cria_Dados_Filial(f->filiais[i],produtos,clientes);
	}
	return f;
}

/*********************************
	FUNCOES DA ESTRUTURA FILIAL
**********************************/

Filial cria_Dados_Filial(Filial filial, Cat_Produtos produtos, Cat_Clientes clientes) {
    filial->produtos = clone_Catalogo(get_Catalogo(produtos));
    filial->clientes = clone_Catalogo(get_CatalogoCli(clientes));
    return filial;
}


Filial init_Filial() {
	Filial f = (Filial) malloc(sizeof(struct filial));
	f->clientes = init_Catalogo(26);
	f->produtos = init_Catalogo(26);
	return f;
}


Filial adiciona_Venda_Filial(Filial f, Venda v) {
	Produto product = getProduto(v);
	Cliente client = getCliente(v);
	char* cli = getNomeCliente(client);
	char* prod = getNomeProduto(product);
	int quant = getQuantidade(v);
	char promocao = getPromocao(v);
	int promo = (promocao == 'N') ? NORMAL : PROMOCAO;
	int indexP = prod[0] - 'A';

	Nodo_Produtos nodo_p = getEstrutura_Catalogo(f->produtos,prod,indexP);
	
	if(!nodo_p) {
		nodo_p = init_Nodo_Produtos();
	}
	nodo_p->quantidade += quant;
	if(promo == NORMAL) nodo_p->clientes_N = adiciona_Nome(nodo_p->clientes_N,cli);
	else nodo_p->clientes_P = adiciona_Nome(nodo_p->clientes_P,prod);

	f->produtos = insere_Catalogo(f->produtos,prod,nodo_p,indexP);

	return f;
}

/****************************************
	FUNCOES DA ESTRUTURA DE CADA PRODUTO
****************************************/


Nodo_Produtos init_Nodo_Produtos() {
	Nodo_Produtos produto = (Nodo_Produtos) malloc(sizeof(struct nodo_produtos));
	produto->quantidade = 0;
	produto->clientes_N = init_Conj_Filiais(100);
	produto->clientes_P = init_Conj_Filiais(100);

	return produto;
}


/***********
	FUNCOES DE LISTAS
***********/

Conj_Filiais init_Conj_Filiais(int n) {
	Conj_Filiais c = (Conj_Filiais) malloc(sizeof(struct conjunto_filiais));
	c->lista = init_Array(n);
	return c;
}


Conj_Filiais adiciona_Nome(Conj_Filiais c, char* nome) {
	c->lista = adiciona_array(c->lista,nome);
	return c;
}


/*********************
	FUNCOES GENERICAS
**********************/


