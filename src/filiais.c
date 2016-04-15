#include "./headers/filiais.h"


struct filial{
    Catalogo clientes;
    Catalogo produtos;
};

/*Estrutura inserida em cada nodo referente a um cliente */

typedef struct nodo_clientes {
    Catalogo Produtos_Cliente;
    int total[12];
} *Nodo_Clientes;

/*Estrutura inserida em cada nodo referente a um produto */

typedef struct nodo_produtos{
	int quantidade;
	Conj_Filiais clientes_N;
	Conj_Filiais clientes_P;
} *Nodo_Produtos;


struct conjunto_filiais {
	Array lista;
};

struct listaFilial{
	ListaFi lista[12];
};

struct listafi {
    char** array;
    int pos;
    int capacidade;
    float *custo;

};


/*********************************
	FUNCOES DA ESTRUTURA FILIAL
**********************************/

/**
 * Adiciona dados a uma filial.
 * @param Filial filial.
 * @param Cat_Produtos produtos.
 * @param Cat_Clientes clientes.
 * @return Filial.
 */
Filial cria_Dados_Filial(Filial filial, Cat_Produtos produtos, Cat_Clientes clientes) {
    filial->produtos = clone_Catalogo(get_Catalogo(produtos));
    filial->clientes = clone_Catalogo(get_CatalogoCli(clientes));
    return filial;
}

/**
 * Inicializa uma filial.
 * @return Filial.
 */
Filial init_Filial() {
	Filial f = (Filial) malloc(sizeof(struct filial));
	f->clientes = init_Catalogo(26);
	f->produtos = init_Catalogo(26);
	return f;
}

/**
 * Adiciona dados de uma venda a uma filial.
 * @param Filial f.
 * @param Venda v.
 * @return Filial.
 */
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


/**
 * Inicia um Nodo de produtos.
 * @return Nodo_Produtos.
 */
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

/**
 * Inicia um conjunto de filiais.
 * @param int n.
 * @return Conj_Filiais.
 */
Conj_Filiais init_Conj_Filiais(int n) {
	Conj_Filiais c = (Conj_Filiais) malloc(sizeof(struct conjunto_filiais));
	c->lista = init_Array(n);
	return c;
}

/**
 * Adiciona um nome ao array do conjuto de filiais.
 * @param Conj_Filiais c.
 * @param char *nome.
 * @return Conj_Filiais.
 */
Conj_Filiais adiciona_Nome(Conj_Filiais c, char* nome) {
	c->lista = adiciona_array(c->lista,nome);
	return c;
}


/*********************
	FUNCOES GENERICAS
**********************/
