#include "./headers/faturacao.h"

#define NORMAL 0
#define PROMOCAO 1

#define NR_MESES 12


struct fatura_produto {
	int total_vendas;
	double total_faturacao;
	int quantidades[2][3];
	double precos[2][3];
};


struct faturacao {
	Catalogo meses[12];
};



Faturacao init_Faturacao() {
	int i;
	Faturacao fat = (Faturacao) malloc(sizeof(struct faturacao));
	for(i = 0; i < NR_MESES; i++) {
		fat->meses[i] = init_Catalogo();
	}
	return fat;
}


Faturacao cria_Dados_Faturacao(Faturacao fat, Cat_Produtos prods) {
	int i;
	for (i = 0; i < NR_MESES; i++) {
		fat->meses[i] = clone_Catalogo(get_Catalogo(prods));
	}
	return fat;
}


Fatura_Produto init_Fatura_Produto() {
	int i, j;
	Fatura_Produto fatura = (Fatura_Produto) malloc(sizeof(struct fatura_produto));
	fatura->total_vendas = 0;
	fatura->total_faturacao = 0;
	for(i = 0; i < 2; i++) {
		for(j = 0; j < 3; j++) {
			fatura->quantidades[i][j] = 0;
			fatura->precos[i][j] = 0;
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
	
	Fatura_Produto estrutura = getEstrutura_Catalogo(contas->meses[mes],prod);
	
	if(estrutura == NULL) {
		estrutura = init_Fatura_Produto();
	}

	estrutura->total_vendas += quantidades;
	estrutura->total_faturacao += custo;
	estrutura->quantidades[promo][filial] += quantidades;
	estrutura->precos[promo][filial] += custo;
	contas->meses[mes] = insere_Catalogo(contas->meses[mes],prod,estrutura);
	
	return contas;
}
