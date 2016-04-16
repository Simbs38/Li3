#include "./headers/filiais.h"


struct filial{
    Catalogo clientes;
    Catalogo produtos;
};

/*Estrutura inserida em cada nodo referente a um cliente */

typedef struct nodo_clientes {
    AVL meses_produtos[12]; /* catálogo com 12 avl's para inserção dos produtos com base no mês */
    int total_quantidades[12];
} *Nodo_Clientes;


/* Estrutura inserida em cada produto associado a cada cliente */

typedef struct lista_produtos {
	int quantidade;
	double faturacao;
	char produto[7];
} *Lista_Produtos;


/*Estrutura inserida em cada nodo referente a um produto */

typedef struct nodo_produtos{
	int quantidade;
	Conj_Filiais clientes_N;
	Conj_Filiais clientes_P;
} *Nodo_Produtos;



struct conjunto_filiais {
	Array lista;
};


Nodo_Clientes init_Nodo_Clientes();
Lista_Produtos init_Lista_Produtos();
Nodo_Produtos init_Nodo_Produtos();


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
	
	char* prod = getNomeProduto(getProduto(v));
	/*printf("produto: |%s|\n",prod);*/
	char* cli = getNomeCliente(getCliente(v));
/*	printf("cliente: |%s|\n",cli);*/
	int quant = getQuantidade(v);
/*	printf("quantidade: %d\n",quant);*/
	char promocao = getPromocao(v);
	int promo = (promocao == 'N') ? NORMAL : PROMOCAO;
/*	printf("promocao: %d\n",promo);*/
	int mes = getMes(v) - 1;
/*	printf("mes: %d\n", mes);*/
	double price = getPreco(v);
/*	printf("preco: %f\n",price);*/
	double faturado = quant * price;
/*printf("faturado: %f\n\n",faturado);*/ 
	
	/* INFO DOS PRODUTOS */

	
	Nodo_Produtos nodo_p = getEstrutura_Catalogo(f->produtos,prod);
	
	if(!nodo_p) {
		nodo_p = init_Nodo_Produtos();
	}
	
	nodo_p->quantidade += quant;
	
	if(promo == NORMAL) nodo_p->clientes_N = adiciona_Nome(nodo_p->clientes_N,cli);
	else nodo_p->clientes_P = adiciona_Nome(nodo_p->clientes_P,cli);
	
	f->produtos = insere_Catalogo(f->produtos,prod,nodo_p);
	
	
	/* INFO DOS CLIENTES */

	
	Nodo_Clientes nodo_c = getEstrutura_Catalogo(f->clientes,cli);

	if(!nodo_c) {
		nodo_c = init_Nodo_Clientes();
	}

	nodo_c->total_quantidades[mes] += quant;
	
	Lista_Produtos prod_c = avl_getEstrutura(nodo_c->meses_produtos[mes],prod);

	if(!prod_c) {
		prod_c = init_Lista_Produtos();
	}

	prod_c->faturacao += faturado;
	prod_c->quantidade += quant;
	strcpy(prod_c->produto,prod);

	nodo_c->meses_produtos[mes] = avl_insert(nodo_c->meses_produtos[mes],prod,prod_c);

	f->clientes = insere_Catalogo(f->clientes,cli,nodo_c);

	return f;
}



Boolean verifica_cliente_comprado(Filial f, char* c) {
	Nodo_Clientes n = getEstrutura_Catalogo(f->clientes,c);
	if(n) return true;
	else return false;
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


/****************************************
	FUNCOES DA ESTRUTURA DE CADA CLIENTE
****************************************/


Nodo_Clientes init_Nodo_Clientes() {
	int i;
	Nodo_Clientes cliente = (Nodo_Clientes) malloc(sizeof(struct nodo_clientes));
	for(i = 0; i < 12; i++) {
		cliente->meses_produtos[i] = initAVL();
		cliente->total_quantidades[i] = 0;
	}
	return cliente;
}



Lista_Produtos init_Lista_Produtos() {
	Lista_Produtos l = (Lista_Produtos) malloc(sizeof(struct lista_produtos));
	l->quantidade = 0;
	l->faturacao = 0;
	return l;
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


void apresenta_Dados_Filial(Conj_Filiais c) {
	apresenta_Array(c->lista);
}


int filial_getPos(Conj_Filiais conjunto) {
	return catalogo_getPos(conjunto->lista);
}


char* filial_get_elemento_lista(Conj_Filiais conjunto, int pos) {
	return catalogo_getElemento(conjunto->lista,pos);
}

/*********************
	FUNCOES GENERICAS
**********************/


int nr_total_unidades_compradas(Filial f, char* cliente, int mes) {

	Nodo_Clientes nodo_c = getEstrutura_Catalogo(f->clientes,cliente);

	if(!nodo_c) {
		return 0;
	}
	else {
		return nodo_c->total_quantidades[mes-1];
	}
}



Conj_Filiais lista_clientes_compraram_filial(Conj_Filiais c, Filial f) {
	c->lista = catalogo_clientes_compraram_filial(c->lista, f->clientes);
	return c;
}


Conj_Filiais lista_clientes_de_produto(Filial f, char* produto, char promo) {
	Nodo_Produtos nodo_p = getEstrutura_Catalogo(f->produtos,produto);
	if(!nodo_p) return NULL;
	else {
		if(promo == 'N') return nodo_p->clientes_N;
		else return nodo_p->clientes_P;
	}
}