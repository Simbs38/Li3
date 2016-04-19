#include "./headers/produtos.h"

#include <string.h>
#include <stdlib.h>


struct produto {
  char prod[7];
};


struct catalogo_produtos{
  Catalogo catalogo;
};

struct conjunto_produtos {
  Array lista;
};


Cat_Produtos init_cat_produtos() {
  Cat_Produtos catalog = (Cat_Produtos) malloc(sizeof(struct catalogo_produtos));
  catalog->catalogo = init_Catalogo();
  return catalog;
}


Produto criaProduto() {
	Produto product = (Produto) malloc(sizeof(struct produto));
	return product;
}


char* getNomeProduto(Produto product, char* novo) {
  novo = malloc(7*sizeof(char));
  strncpy(novo,product->prod,7);
  return novo;
}


Produto alteraProduto(Produto product, char* info) {
  strncpy(product->prod,info,7);
  return product;
}


void free_produto(Produto product) {
  free(product);
}


Boolean existe_Produto(Cat_Produtos products, Produto product) {
  return existe_Catalogo(products->catalogo,product->prod);
}


Cat_Produtos insere_produto(Cat_Produtos products, Produto product) {
  products->catalogo = insere_Catalogo(products->catalogo,product->prod,NULL);
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
  Cat_Produtos novo = init_cat_produtos();
  novo->catalogo = clone_Catalogo(products->catalogo);
  return novo;
}


Catalogo get_Catalogo_Produtos(Cat_Produtos products) {
  Catalogo novo = clone_Catalogo(products->catalogo);
  return novo;
}


Conj_Produtos init_Conjunto(int capacidade) {
  Conj_Produtos conjunto = (Conj_Produtos) malloc(sizeof(struct conjunto_produtos));
  conjunto->lista = init_Array(capacidade);
  return conjunto;
}


Conj_Produtos converte_Produtos(Conj_Produtos conjunto, Cat_Produtos products, char letra) {
  conjunto->lista = lista_catalogo_letra(conjunto->lista,products->catalogo,letra);
  return conjunto;
}


void free_Conj_Produtos(Conj_Produtos c) {
  free_Array(c->lista);
  free(c);
}


void apresenta_Produtos(Conj_Produtos conjunto) {
  apresenta_Array(conjunto->lista);
}