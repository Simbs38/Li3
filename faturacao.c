#include "faturacao.h"

#define NR_LETRAS 26
#define NORMAL 0
#define PROMOCAO 1


struct fatura_produto {
	int total_vendas;
	int quantidades[12][3][2];
	double precos[12][3][2];
};


struct faturacao {
	Catalogo faturas;

};


Faturacao init_Faturacao() {
	Faturacao fat = (Faturacao) malloc(sizeof(struct faturacao));
	fat->faturas = init_Catalogo(NR_LETRAS);
	return fat;
}


Faturacao cria_Dados_Faturacao(Faturacao fat, Cat_Produtos prods) {
	fat->faturas = clone_Catalogo(get_Catalogo(prods));
	return fat;
}


Fatura_Produto init_Fatura_Produto() {
	int i, j, k;
	Fatura_Produto fatura = (Fatura_Produto) malloc(sizeof(struct fatura_produto));
	fatura->total_vendas = 0;
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
	printf("%s\n",prod);
	int mes = getMes(venda) - 1;
	int filial = getFilial(venda) - 1;
	char promocao = getPromocao(venda);
	int promo = (promocao == 'N') ? NORMAL : PROMOCAO;  
	int quantidades = getQuantidade(venda);
	double price = getPreco(venda);
	double custo = quantidades * price;
	Fatura_Produto estrutura = getEstrutura_Catalogo(contas->faturas,prod);
	if(estrutura == NULL) {
		estrutura = init_Fatura_Produto();
	}
	estrutura->total_vendas += quantidades;
	estrutura->quantidades[mes][filial][promo] += quantidades;
	estrutura->precos[mes][filial][promo] += custo;
	imprime_estrutura(estrutura);
	contas->faturas = insere_Catalogo(contas->faturas,prod,estrutura);
	
	return contas;
}

void imprime_estrutura(Fatura_Produto fatura) {
	int i, j, k;
	for(i = 0; i < 12; i++) {
		for(j = 0; j < 3; j++) {
			for(k = 0; k < 2; k++) {
				printf("%d\n",fatura->quantidades[i][j][k] = 0);
				printf("%f\n",fatura->precos[i][j][k] = 0);
			}
		}
	}
}