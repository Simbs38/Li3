#include "faturacao.h"


struct fatura_produto {
	int quantidades[12][6];
	double precos[12][6];
	int total_vendas;
};


struct faturacao {
	Catalogo faturas;
};


Faturacao init_Faturacao() {
	Faturacao fat = (Faturacao) malloc(sizeof(struct faturacao));
	fat->faturas = init_Catalogo();
	return fat;
}


Faturacao cria_Dados_Faturacao(Faturacao fat, Cat_Produtos prods) {
	fat->faturas = clone_Catalogo(get_Catalogo(prods));
	return fat;
}
