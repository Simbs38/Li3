#include "./headers/faturacao.h"

#define NORMAL 0
#define PROMOCAO 1
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


Faturacao cria_Dados_Faturacao(Faturacao fat, Cat_Produtos prods) {
		fat->faturas = clone_Catalogo(get_Catalogo(prods));
	return fat;
}


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

int get_total_quantidades_intervalo(Faturacao fatura, int mes1, int mes2) {
	int i, total = 0;
	if(mes1 <= mes2) {
		for(i = mes1-1; i <= mes2-1; i++){
			total += fatura->total_vendas[i];
		}
	}
	else {
		for(i = mes2-1; i <= mes1-1; i++){
			total += fatura->total_vendas[i];
		}
	}
	return total;
}


double get_total_faturado_intervalo(Faturacao fatura, int mes1, int mes2) {
	int i; 
	double total = 0;
	if(mes1 <= mes2) {
		for(i = mes1-1; i <= mes2-1; i++){
			total += fatura->total_faturado[i];
		}
	}
	else {
		for(i = mes2-1; i <= mes1-1; i++){
			total += fatura->total_faturado[i];
		}
	}
	return total;
}

Conj_Faturas init_Lista_Faturacao(int capacidade) {
  Conj_Faturas conjunto = (Conj_Faturas) malloc(sizeof(struct conjunto_faturas));
  conjunto->lista = init_Array(capacidade);
  return conjunto;
}


Conj_Faturas faturas_produtos_nao_comprados_totais(Conj_Faturas conjunto, Faturacao faturacao) {
	conjunto->lista = catalogo_produtos_nao_comprados_totais(conjunto->lista, faturacao->faturas);
	return conjunto;
}


Conj_Faturas adiciona_Conjunto(Conj_Faturas conjunto, char* info) {
	conjunto->lista = adiciona_array(conjunto->lista,info);
	return conjunto;
}

void apresenta_faturas(Conj_Faturas conjunto) {
	apresenta_Array(conjunto->lista);
}