#include "./headers/faturacao.h"

#define NR_LETRAS 26
#define NORMAL 0
#define PROMOCAO 1
#define NR_MESES 12

struct fatura_produto {
	int total_vendas;
	double total_faturacao;
	int quantidades[12][3][2]; /* quantidades[meses][filiais][normal/promocao] */
	double precos[12][3][2];
};


struct faturacao {
	Catalogo meses;
};



Faturacao init_Faturacao() {
	int i;
	Faturacao fat = (Faturacao) malloc(sizeof(struct faturacao));
	fat->meses = init_Catalogo(NR_MESES);
	return fat;
}


Faturacao cria_Dados_Faturacao(Faturacao fat, Cat_Produtos prods) {
		fat->meses = clone_Catalogo(get_Catalogo(prods));
	return fat;
}


Fatura_Produto init_Fatura_Produto() {
	int i, j, k;
	Fatura_Produto fatura = (Fatura_Produto) malloc(sizeof(struct fatura_produto));
	fatura->total_vendas = 0;
	fatura->total_faturacao = 0;
	for(i = 0; i < 12; i++) {
		for(j = 0; i < 3; i++) {
			for(k = 0; j < 2; j++) {
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
	
	Fatura_Produto estrutura = getEstrutura_Catalogo(contas->meses,prod,prod[0]-'A');
	
	if(estrutura == NULL) {
		estrutura = init_Fatura_Produto();
	}	
	
	estrutura->total_vendas += quantidades;
	estrutura->total_faturacao += custo;
	estrutura->quantidades[mes][filial][promo] += quantidades;
	estrutura->precos[mes][filial][promo] += custo;
	contas->meses = insere_Catalogo(contas->meses,prod,estrutura,prod[0]-'A');	
	
	return contas;
}
