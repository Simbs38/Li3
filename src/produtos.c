#include "./headers/produtos.h"

#define NR_LETRAS 26
#define MAXSIZEPRODUTOS 64


struct produto {
  char prod[7];
};


struct catalogo_produtos{
  Catalogo catalogo;
};

struct conjunto_produtos {
  Array lista;
};


/**
 * Inicializa um catalogo de produtos.
 * @return Cat_Produtos.
 */
Cat_Produtos init_cat_produtos() {
  Cat_Produtos catalog = malloc(sizeof(struct catalogo_produtos));
  catalog->catalogo = init_Catalogo(NR_LETRAS);
  return catalog;
}


/**
 * Aloca e retorna um produto.
 * @return Produto.
 */
Produto criaProduto() {
	Produto product = (Produto) malloc(sizeof(struct produto));

	return product;
}

/**
 * Devolve o codigo de um produto.
 * @param Produto product.
 * @return char *.
 */
char* getNomeProduto(Produto product) {
  return product->prod;
}
/**
 * Altera a informação de um produto.
 * @param Produto product.
 * @param char *info.
 */
void alteraProduto(Produto product, char *info) {
  strncpy(product->prod, info, 7);
}

/**
 * Liberta o espaço alocado por um produto.
 * @param Produto product.
 */
void free_produto(Produto product) {
  free(product);
}

/**
 * Função que verifica se um dado produto existe no catalogo de clientes.
 * @param Cat_Produtos products.
 * @param Produto product.
 * @return Boolean com valor de verdade.
 */
Boolean existe_Produto(Cat_Produtos products, Produto product) {
  return existe_Catalogo(products->catalogo,product->prod,product->prod[0]-'A');
}

/**
 * Insere um produto no catalogo de produtos.
 * @param Cat_Produtos products.
 * @param Produto product.
 * @return Cat_Produtos.
 */

Cat_Produtos insere_produto(Cat_Produtos products, Produto product) {
  products->catalogo = insere_Catalogo(products->catalogo,product->prod,NULL,product->prod[0]-'A');
  return products;
}

/**
 * Devolve o numero de produtos num catalogo.
 * @param Cat_Produtos products.
 * @return int.
 */
int total_Produtos(Cat_Produtos products) {
  return total_elems_Catalogo(products->catalogo);
}

/**
 * Devolve o numero de produtos começados com a letra indicada.
 * @param Cat_Produtos products.
 * @param char letra.
 * @return int.
 */

int total_Produtos_letra(Cat_Produtos products, char letra) {
  return total_elems_letra(products->catalogo,letra);
}

/**
 * Liberta o espaço alocado em memoria pelo catalogo.
 * @param Cat_Produtos  products.
 */
void remove_Catalogo_Produtos(Cat_Produtos products) {
  remove_Catalogo(products->catalogo);
  free(products);
}

/**
 * Cria um clone de um catalogo de produtos, retornando o endereço do novo catalogo.
 * @param Cat_Produtos products.
 * @return Cat_Produtos.
 */
Cat_Produtos clone_Catalogo_Produtos(Cat_Produtos products) {
  Cat_Produtos novo;
  novo->catalogo = clone_Catalogo(products->catalogo);
  return novo;
}

/**
 * Retorna o catalogo de produtos dentro da estrutura.
 * @param Cat_Produtos products.
 * @return Catalogo.
 */
Catalogo get_Catalogo(Cat_Produtos products) {
  return products->catalogo;
}

/**
 * Converte de um catalogo de produtos para um conjunto de produtos.
 * @param Conj_Produtos conjunto.
 * @param Cat_Produtos products.
 * @param char letra.
 * @return Conj_Produtos.
 */
Conj_Produtos converte_Produtos(Conj_Produtos conjunto, Cat_Produtos products, char letra) {
  conjunto->lista = lista_catalogo_letra(conjunto->lista,products->catalogo,letra);
  return conjunto;
}

/**
 * Inicializa um conjunto de produtos.
 * @param int capacidade.
 * @return Conj_Produtos.
 */
Conj_Produtos init_Conjunto(int capacidade) {
  Conj_Produtos conjunto = (Conj_Produtos) malloc(sizeof(struct conjunto_produtos));
  conjunto->lista = init_Array(capacidade);
  return conjunto;
}

/**
 * Prepara os dados para serem apresentados.
 * @param Conj_Produtos conjunto.
 * @return Conj_Produtos.
 */
void apresenta_Produtos(Conj_Produtos conjunto) {
  apresenta_Array(conjunto->lista);
}