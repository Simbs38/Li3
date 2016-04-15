#include "./headers/faturacao.h"


#define NR_LETRAS 26

struct fatura_produto {
	int quantidades[12][3][2]; /* quantidades[meses][filiais][normal/promocao] */
	double precos[12][3][2];
};


struct faturacao {
	Catalogo faturas;
	int total_vendas[12];
	double total_faturado[12];
};

struct conjunto_faturas {
	Array lista;
};

/**
 * Inicializa a estrutura Faturacao.
 * @return Faturacao.
 */

Faturacao init_Faturacao() {
	int i;
	Faturacao fat = (Faturacao) malloc(sizeof(struct faturacao));
		fat->faturas = init_Catalogo(NR_LETRAS);
		for(i = 0; i < 12; i++) {
			fat->total_faturado[i] = 0;
			fat->total_vendas[i] = 0;
		}
	return fat;
}

/**
 * Insere os dados dos produtos na estrutura.
 * @param Faturacao fat.
 * @param Cat_Produtos prods.
 * @return Faturacao.
 */

Faturacao cria_Dados_Faturacao(Faturacao fat, Cat_Produtos produtos) {
		fat->faturas = clone_Catalogo(get_Catalogo(produtos));
	return fat;
}
/**
 * Liberta o espaço alocado em memoria para a estrutura.
 * @param Faturacao fatutacao.
 */
void free_Faturacao(Faturacao faturacao) {
	remove_Catalogo(faturacao->faturas);
	free(faturacao);
}

/**
 * Inicializa as faturações de um produto.
 * @return Fatura_Produto.
 */
Fatura_Produto init_Fatura_Produto() {
	int i, j, k;
	Fatura_Produto fatura = (Fatura_Produto) malloc(sizeof(struct fatura_produto));
	for(i = 0; i < 12; i++) {
		for(j = 0; j < 3; j++) {
			for(k = 0; k < 2; k++) {
				fatura->quantidades[i][j][k] = 0;
				fatura->precos[i][j][k] = 0;
			}
		}
	}
	return fatura;
}

/**
 * Adiciona uma venda a faturação total.
 * @param Faturacao contas
 * @param Venda venda
 * @return Faturacao.
 */	
Faturacao adiciona_Fatura(Faturacao contas, Venda venda) {
	
	Produto product = getProduto(venda);
	char* prod = getNomeProduto(product);
	int mes = getMes(venda) - 1;
	int filial = getFilial(venda) - 1;

	char promocao = getPromocao(venda);
	int promo = (promocao == 'N') ? NORMAL : PROMOCAO;  
	int quantidades = getQuantidade(venda);
	double price = getPreco(venda);
	double custo = quantidades * price;

	

	Fatura_Produto estrutura = getEstrutura_Catalogo(contas->faturas,prod,prod[0]-'A');

	
	if(estrutura == NULL) {
		estrutura = init_Fatura_Produto();
	}
	contas->total_vendas[mes] += quantidades;
	contas->total_faturado[mes] += custo;
	estrutura->quantidades[mes][filial][promo] += quantidades;
	estrutura->precos[mes][filial][promo] += custo;
	contas->faturas = insere_Catalogo(contas->faturas,prod,estrutura,prod[0]-'A');	
	
	return contas;
}

/**
 * Devolve a estrutura alocada junto de um produto.
 * @param Faturacao faturacao.
 * @param char* produto.
 * @return void *.
 */
void* getEstrutura_Faturacao(Faturacao faturacao, char* produto) {
	return getEstrutura_Catalogo(faturacao->faturas,produto,produto[0]-'A');
}

/**
 * Devolve a quantidade total de um produto num dado mês em promoção ou em preço normal.
 * @param Faturacao fatura.
 * @param char* produto.
 * @param int mes.
 * @param char modo.
 * @return int.
 */
int get_total_quantidades_mes_produto(Faturacao fatura, char* produto, int mes, char modo) {
	int i;
	
	int total = 0;
	
	Fatura_Produto anexo = getEstrutura_Catalogo(fatura->faturas,produto,produto[0]-'A');
	
	if(anexo != NULL) {
	
	for(i = 0; i < 3; i++) {
		if(modo == 'N') total += anexo->quantidades[mes-1][i][NORMAL];
		else if(modo == 'P') total += anexo->quantidades[mes-1][i][PROMOCAO];
	}
	
	return total;
	
	} else return 0;
}

/**
 * Devolve o custo total de um produto num dado mês em promoção ou em preço normal.
 * @param Faturacao fatura.
 * @param char* produto.
 * @param int mes.
 * @param char modo.
 * @return int.
 */
double get_total_precos_mes_produto(Faturacao fatura, char* produto, int mes, char modo) {
	double total = 0;
	int i;
	
	Fatura_Produto anexo = getEstrutura_Catalogo(fatura->faturas,produto,produto[0]-'A');
	
	if(anexo != NULL) {

	for(i = 0; i < 3; i++) {
		if(modo == 'N') total += anexo->precos[mes-1][i][NORMAL];
		else if(modo == 'P') total += anexo->precos[mes-1][i][PROMOCAO];
	}
	
	return total;
	}

	else return 0;
}

/**
 * Devolve a quantidade total de um produto num dado mês e numa dada filial em promoção ou em preço normal.
 * @param Faturacao fatura.
 * @param char* produto.
 * @param int mes.
 * @param char modo.
 * @param int filial.
 * @return int.
 */
int get_total_quantidades_mes_produto_filial(Faturacao fatura, char* produto, int mes, char modo, int filial) {
	int i;
	
	int total = 0;
	
	Fatura_Produto anexo = getEstrutura_Catalogo(fatura->faturas,produto,produto[0]-'A');
	
	if(anexo != NULL) {
	
		if(modo == 'N') total += anexo->quantidades[mes-1][filial-1][NORMAL];
		else if(modo == 'P') total += anexo->quantidades[mes-1][filial-1][PROMOCAO];
	
	return total;
	
	} else return 0;
}

/**
 * Devolve o custo total de um produto num dado mês e numa dada filial em promoção ou em preço normal.
 * @param Faturacao fatura.
 * @param char* produto.
 * @param int mes.
 * @param char modo.
 * @param int filial.
 * @return int.
 */
double get_total_precos_mes_produto_filial(Faturacao fatura, char* produto, int mes, char modo, int filial) {
	int i;
	double total = 0;
	
	Fatura_Produto anexo = getEstrutura_Catalogo(fatura->faturas,produto,produto[0]-'A');
	
	if(anexo != NULL) {
	
		if(modo == 'N') total += anexo->precos[mes-1][filial-1][NORMAL];
		else if(modo == 'P') total += anexo->precos[mes-1][filial-1][PROMOCAO];
	
	return total;
	
	} else return 0;
}

/**
 * Devolve a quantidade total vendida num intervalo de meses.
 * @param Faturacao fatura.
 * @param int mes1.
 * @param int mes2.
 * @return int.
 */
int get_total_quantidades_intervalo(Faturacao fatura, int mes1, int mes2) {
	int i, total = 0;

	for(i = mes1-1; i <= mes2-1; i++){
		total += fatura->total_vendas[i];
	}

	return total;
}


/**
 * Devolve o total faturado num intervalo de meses.
 * @param Faturacao fatura.
 * @param int mes1.
 * @param int mes2.
 * @return double.
 */
double get_total_faturado_intervalo(Faturacao fatura, int mes1, int mes2) {
	int i; 
	double total = 0;

	for(i = mes1-1; i <= mes2-1; i++){
		total += fatura->total_faturado[i];
	}

	return total;
}

/**
 * Inicializa uma lista de faturação.
 * @param int capacidade.
 * @return Conj_Faturas.
 */
Conj_Faturas init_Lista_Faturacao(int capacidade) {
  Conj_Faturas conjunto = (Conj_Faturas) malloc(sizeof(struct conjunto_faturas));
  conjunto->lista = init_Array(capacidade);
  return conjunto;
}

/**
 * Devolve o conjuto de produtos nunca comprados.
 * @param Conj_Faturas conjuto.
 * @param Faturacao faturacao.
 * @return Conj_Faturas.
 */
Conj_Faturas faturas_produtos_nao_comprados_totais(Conj_Faturas conjunto, Faturacao faturacao) {
	conjunto->lista = catalogo_produtos_nao_comprados_totais(conjunto->lista, faturacao->faturas);
	return conjunto;
}

/**
 * Adiciona ao conjuto de faturas um produto.
 * @param Conj_Faturas conjuto.
 * @param char *info.
 * @return Conj_Faturas.
 */
Conj_Faturas adiciona_Conjunto(Conj_Faturas conjunto, char* info) {
	conjunto->lista = adiciona_array(conjunto->lista,info);
	return conjunto;
}

/**
 * Cria uma lista com todos os produtos da estrutura.
 * @param Conj_Faturas conjuto.
 * @param Faturacao faturacao.
 * @return Conj_Faturas.
 */
Conj_Faturas cria_lista_total(Conj_Faturas conjunto, Faturacao faturacao) {
	conjunto->lista = catalogo_lista_total(conjunto->lista,faturacao->faturas);
	return conjunto;
}

/**
 * ??????????????????????????????????????????????????????????????.
 * @param Conj_Faturas conjuto.
 * @param Conj_Faturas nao_comprados.
 * @param Faturacao faturas.
 * @param int filial.
 * @return Conj_Faturas.
 */
Conj_Faturas faturas_nao_comprado_filial(Conj_Faturas conjunto, Conj_Faturas nao_comprados,  Faturacao faturas, int filial) {
	int tamanho = faturacao_getPos(conjunto);
	Fatura_Produto estrutura;
	int i = 0;
	int j, var = 0;
	char* prod;
	while(i < tamanho) {
		prod = get_elemento_lista(conjunto,i);
		estrutura = getEstrutura_Faturacao(faturas,prod);
		if(estrutura) {
			for(j = 0; j < 12 && !var; j++) {
				if(estrutura->quantidades[j][filial-1][0] != 0) var++;
				if(estrutura->quantidades[j][filial-1][1] != 0) var++;
			}
		}
		if(var == 0) adiciona_Conjunto(nao_comprados,prod);
		var = 0;
		i++;
	}
	return nao_comprados;
}


/**
 * Devolve um produto de uma lista.
 * @param Conj_Faturas conjuto.
 * @param int pos.
 * @return char*.
 */
char* get_elemento_lista(Conj_Faturas conjunto, int pos) {
	return catalogo_getElemento(conjunto->lista,pos);
}


/**
 * Devolve a posiçao de um ????????????????????.
 * @param Conj_Faturas conjuto.
 * @return int.
 */
int faturacao_getPos(Conj_Faturas conjunto) {
	return catalogo_getPos(conjunto->lista);
}


/**
 * Prepara o conjuto de faturas para ser apresentado.
 * @param Conj_Faturas conjuto.
 */
void apresenta_faturas(Conj_Faturas conjunto) {
	apresenta_Array(conjunto->lista);
}