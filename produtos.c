#include "produtos.h"

#define NR_LETRAS 26


struct produto {
  char* prod;
};

struct catalogo_produtos{
  Catalogo catalogo;
};

Cat_Produtos init_cat_produtos() {
  Cat_Produtos catalog = malloc(sizeof(struct catalogo_produtos));
  catalog->catalogo = init_Catalogo();
  return catalog;
}

Produto criaProduto(char* info) {
	struct produto* product = (struct produto*) malloc(sizeof(struct produto));
	product->prod = malloc(MAXSIZEPRODUTOS);
  strcpy(product->prod,info);
	return product;
}

void alteraProduto(Produto product, char *info) {
  strcpy(product->prod,info);
}

/* Função que verifica se um dado produto existe no catalogo de produtos */

Boolean existe_Produto(Cat_Produtos products, Produto product) {
  return existe_Catalogo(products->catalogo,getNomeProduto(product));
}


Cat_Produtos insere_produto(Cat_Produtos products, Produto product) {
  products->catalogo = insere_Catalogo(products->catalogo,getNomeProduto(product));
  return products;
}


int total_Produtos(Cat_Produtos products) {
  return total_elems_Catalogo(products->catalogo);
}


int total_Produtos_letra(Cat_Produtos products, char letra) {
  return total_elems_letra(products->catalogo,letra);
}


void remove_Catalogo_Produtos(Cat_Produtos products) {
  remove_Catalogo(products->catalogo);
  free(products);
}

char* getNomeProduto(Produto product) {
  return product->prod;
}