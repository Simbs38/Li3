#include "faturacao.h"


struct fatura_produto {
	int quantidades[12][12];
	double precos[12][6];
	int total_vendas;
};


struct faturacao {
	AVL indice[26];
};


Faturacao adiciona_Fatura(Faturacao contas, Venda venda) {
	int index = getProduto(venda)[0] - 'A';
	contas = avl_insere(contas->indice[index],getProduto(venda),cria_Fatura(venda));
} 

Fatura cria_Fatura (Venda venda) {
	
	struct fatura_produto* fatura = (struct fatura_produto*) malloc(sizeof(struct fatura_produto));

	
}