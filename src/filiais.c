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


struct heap_filial {
	Heap heap;
};


static Nodo_Clientes init_Nodo_Clientes();
static Lista_Produtos init_Lista_Produtos();
static Nodo_Produtos init_Nodo_Produtos();
HEAP converte_Heap_clientes(HEAP h, AVL a, char ordenacao);
HEAP converte_Heap_clientes_aux(HEAP h, NODO n, char ordenacao);
Boolean existe_Conj_Filiais(Conj_Filiais c, char* valor);
HEAP converte_Heap_produto(HEAP h, AVL a);
HEAP converte_Heap_produtos_aux(HEAP h, NODO n);

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
	
	if(promo == NORMAL && (existe_Conj_Filiais(nodo_p->clientes_N,cli) == false)) nodo_p->clientes_N = adiciona_Nome(nodo_p->clientes_N,cli);
	else if(existe_Conj_Filiais(nodo_p->clientes_P,cli) == false) nodo_p->clientes_P = adiciona_Nome(nodo_p->clientes_P,cli);
	
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


/**
 * Retorna um Boolean caso um dado cliente tenha comprado algum produto.
 * @param f Filial a procurar.
 * @param valor char* a verificar.
 * @return Boolean.
 */
Boolean verifica_cliente_comprado(Filial f, char* c) {
	Nodo_Clientes n = getEstrutura_Catalogo(f->clientes,c);
	if(n) return true;
	else return false;
}


Boolean filial_existe_Cliente(Filial f, char* cliente) {
	return existe_Catalogo(f->clientes,cliente);
}

Boolean filial_existe_Produto(Filial f,char* produto) {
	return existe_Catalogo(f->produtos,produto);
}


/****************************************
	FUNCOES DA ESTRUTURA DE CADA PRODUTO
****************************************/


/**
 * Inicia um Nodo de produtos.
 * @return Nodo_Produtos criado.
 */
static Nodo_Produtos init_Nodo_Produtos() {
	
	Nodo_Produtos produto = (Nodo_Produtos) malloc(sizeof(struct nodo_produtos));
	
	produto->quantidade = 0;
	produto->clientes_N = init_Conj_Filiais(100);
	produto->clientes_P = init_Conj_Filiais(100);

	return produto;
}


int getQuantidadeProduto(Filial f, char* produto) {
	Nodo_Produtos nodo_p = getEstrutura_Catalogo(f->produtos,produto);
	return nodo_p->quantidade;
}

int nr_clientes_de_um_produto(Filial f, char* produto) {
	int nr_produtos;
	Nodo_Produtos nodo_p = getEstrutura_Catalogo(f->produtos,produto);
	nr_produtos = filiais_nr_elementos_diferentes(nodo_p->clientes_N,nodo_p->clientes_P);
	return nr_produtos;
}


/****************************************
	FUNCOES DA ESTRUTURA DE CADA CLIENTE
****************************************/

/**
 * Inicia um Nodo de clientes.
 * @return Nodo_Clientes criado.
 */
static Nodo_Clientes init_Nodo_Clientes() {
	int i;
	Nodo_Clientes cliente = (Nodo_Clientes) malloc(sizeof(struct nodo_clientes));
	for(i = 0; i < 12; i++) {
		cliente->meses_produtos[i] = initAVL();
		cliente->total_quantidades[i] = 0;
	}
	return cliente;
}


/**
 * Inicia uma nova Lista_Produtos.
 * @return Lista_Produtos criada.
 */
static Lista_Produtos init_Lista_Produtos() {
	Lista_Produtos l = (Lista_Produtos) malloc(sizeof(struct lista_produtos));
	l->quantidade = 0;
	l->faturacao = 0;
	return l;
}


/********************
    FUNCOES DE LISTAS
*********************/

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

Boolean existe_Conj_Filiais(Conj_Filiais c, char* valor) {
	return existe_Array(c->lista,valor);
}


int filiais_nr_elementos_diferentes(Conj_Filiais a, Conj_Filiais b) {
	return catalogo_nr_elementos_diferentes(a->lista,b->lista);
}


/************************
    FUNCOES SOBRE HEAPS
************************/


/**
 * Inicia uma nova HEAP.
 * @return HEAP criada.
 */
HEAP init_HEAP() {
	HEAP h = (HEAP) malloc(sizeof(struct heap_filial));
	h->heap = initHeap();
	return h;
}


HEAP lista_codigos_de_clientes(Filial f, HEAP h, char* cliente, int mes, char ordenacao) {
	
	Nodo_Clientes nodo_c = getEstrutura_Catalogo(f->clientes,cliente);
	if(nodo_c) {
		h = converte_Heap_clientes(h,nodo_c->meses_produtos[mes-1],ordenacao);
	}
	return h;
}


HEAP top3_clientes(Filial f, HEAP h, char* cliente, char ordenacao) {
	int i;
	Nodo_Clientes nodo_c = getEstrutura_Catalogo(f->clientes,cliente);
	if(nodo_c) {
		for(i = 0; i < NR_MESES; i++) {
			h = converte_Heap_clientes(h,nodo_c->meses_produtos[i],ordenacao);
		}
	}
	return h;
}


/**
 * Converte uma dada AVL em HEAP.
 * @param HEAP h onde serão colocados os valores.
 * @param AVL a ser convertida.
 * @return HEAP após a conversão.
 */
HEAP converte_Heap_clientes(HEAP h, AVL a, char ordenacao) {
	h = converte_Heap_clientes_aux(h,getNodo(a),ordenacao);
	return h;
}



HEAP converte_Heap_clientes_aux(HEAP h, NODO n, char ordenacao) {
	if(n) {
		h = converte_Heap_clientes_aux(h,getNodoEsq(n),ordenacao);
		char* p = getString(n);
		Lista_Produtos prod_c = getCont(n);
		if(!prod_c) {
			h->heap = heap_push(h->heap,p,0,0,1,ordenacao);
		} else {
			h->heap = heap_push(h->heap,p,prod_c->quantidade,prod_c->faturacao,1,ordenacao);
		}
		h = converte_Heap_clientes_aux(h,getNodoDir(n),ordenacao);
	}
	return h;
}



Conj_Filiais convert_Heap_Lista(Conj_Filiais c, HEAP h, char ordenacao) {
	int i = 0;
	char* prod;
	while(i < heap_count(h->heap)) {
		prod = heap_pop(h->heap,ordenacao);
		c = adiciona_Nome(c,prod);
	}
	return c;
}


Conj_Filiais lista_top3(Conj_Filiais c, HEAP h, char ordenacao) {
	int i = 0;
	char* prod;
	while(i < 3) {
		prod = heap_pop(h->heap,ordenacao);
		c = adiciona_Nome(c,prod);
		i++;
	}
	return c;
}


/******************************************************************************************

	QUERIE 10

******************************************************************************************/


HEAP heap_produtos_mais_vendidos(Filial f, HEAP h) {
	int i;
	AVL aux;
	
	for(i = 0; i < NR_LETRAS; i++) {
		aux = catalogo_getAVL(f->produtos,i);
		h = converte_Heap_produto(h,aux);
	}
	return h;
}



HEAP converte_Heap_produto(HEAP h, AVL a) {
	h = converte_Heap_produtos_aux(h,getNodo(a));
	return h;
}


HEAP converte_Heap_produtos_aux(HEAP h, NODO n) {
	if(n) {
		h = converte_Heap_produtos_aux(h,getNodoEsq(n));
		char* p = getString(n);
		Nodo_Produtos prod_c = getCont(n);
		if(prod_c) {
			h->heap = heap_push(h->heap,p,prod_c->quantidade,0,0,'Q');
		}
		h = converte_Heap_produtos_aux(h,getNodoDir(n));
	}
	return h;
}


Conj_Filiais retira_N_Produtos(Conj_Filiais c, HEAP h, int n) {
	int i = 0;
	char* prod;
	while(i < n) {
		prod = heap_pop(h->heap,'Q');
		c = adiciona_Nome(c,prod);
		i++;
	}
	return c;
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


