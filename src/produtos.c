#include "./headers/produtos.h"

#define NR_LETRAS 26


struct produto {
  char* prod;
};


struct catalogo_produtos{
  Catalogo catalogo;
};

struct conjunto_produtos {
  Array lista;
};


Cat_Produtos init_cat_produtos() {
  Cat_Produtos catalog = malloc(sizeof(struct catalogo_produtos));
  catalog->catalogo = init_Catalogo(NR_LETRAS);
  return catalog;
}


Produto criaProduto() {
	Produto product = (Produto) malloc(sizeof(struct produto));
	product->prod = malloc(MAXSIZEPRODUTOS);

  return product;
}

char* getNomeProduto(Produto product) {
  return product->prod;
}

void alteraProduto(Produto product, char *info) {
  strncpy(product->prod, info, MAXSIZEPRODUTOS);
}


/* Função que verifica se um dado produto existe no catalogo de produtos */

Boolean existe_Produto(Cat_Produtos products, Produto product) {
  return existe_Catalogo(products->catalogo,product->prod);
}


Cat_Produtos insere_produto(Cat_Produtos products, Produto product) {
  products->catalogo = insere_Catalogo(products->catalogo,product->prod,NULL,product->prod[0]-'A');
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

Cat_Produtos clone_Catalogo_Produtos(Cat_Produtos products) {
  Cat_Produtos novo;
  novo->catalogo = clone_Catalogo(products->catalogo);
  return novo;
}

Catalogo get_Catalogo(Cat_Produtos products) {
  return products->catalogo;
}

Conj_Produtos converte_Produtos(Conj_Produtos conjunto, Cat_Produtos products, char letra) {
  conjunto->lista = lista_catalogo(conjunto->lista,products->catalogo,letra);
  return conjunto;
}

Conj_Produtos init_Conjunto(int capacidade) {
  Conj_Produtos conjunto = (Conj_Produtos) malloc(sizeof(struct conjunto_produtos));
  conjunto->lista = init_Array(capacidade);
  return conjunto;
}

void apresenta_Produtos(Conj_Produtos conjunto) {
  apresenta_Array(conjunto->lista);
}