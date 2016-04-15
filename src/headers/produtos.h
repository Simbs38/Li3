#ifndef _produtos_h_
#define _produtos_h_

#include <string.h>
#include <stdlib.h>

#include "catalogo.h"
#include "global.h"

typedef struct catalogo_produtos *Cat_Produtos;
typedef struct produto *Produto;
typedef struct conjunto_produtos *Conj_Produtos;

/**
 * Inicializa um catalogo de produtos.
 * @return Cat_Produtos.
 */
Cat_Produtos init_cat_produtos();

/**
 * Insere um produto no catalogo de produtos.
 * @param Cat_Produtos products.
 * @param Produto product.
 * @return Cat_Produtos.
 */
Cat_Produtos insere_produto(Cat_Produtos products, Produto prod);

/**
 * Cria um clone de um catalogo de produtos, retornando o endereço do novo catalogo.
 * @param Cat_Produtos products.
 * @return Cat_Produtos.
 */
Cat_Produtos clone_Catalogo_Produtos(Cat_Produtos products);

/**
 * Retorna o catalogo de produtos dentro da estrutura.
 * @param Cat_Produtos products.
 * @return Catalogo.
 */
Catalogo get_Catalogo(Cat_Produtos products);

/**
 * Função que verifica se um dado produto existe no catalogo de clientes.
 * @param Cat_Produtos products.
 * @param Produto product.
 * @return Boolean com valor de verdade.
 */
Boolean existe_Produto(Cat_Produtos products, Produto product);

/**
 * Devolve o numero de produtos num catalogo.
 * @param Cat_Produtos products.
 * @return int.
 */
int total_Produtos(Cat_Produtos products);

/**
 * Devolve o numero de produtos começados com a letra indicada.
 * @param Cat_Produtos products.
 * @param char letra.
 * @return int.
 */
int total_Produtos_letra(Cat_Produtos products, char letra);

/**
 * Liberta o espaço alocado em memoria pelo catalogo.
 * @param Cat_Produtos  products.
 */
void remove_Catalogo_Produtos(Cat_Produtos products);

/**
 * Aloca e retorna um produto.
 * @return Produto.
 */
Produto criaProduto();

/**
 * Altera a informação de um produto.
 * @param Produto product.
 * @param char *info.
 */
void alteraProduto(Produto product, char *info);

/**
 * Devolve o codigo de um produto.
 * @param Produto product.
 * @return char *.
 */
char* getNomeProduto(Produto product);

/**
 * Liberta o espaço alocado por um produto.
 * @param Produto product.
 */
void free_produto(Produto product);

/**
 * Converte de um catalogo de produtos para um conjunto de produtos.
 * @param Conj_Produtos conjunto.
 * @param Cat_Produtos products.
 * @param char letra.
 * @return Conj_Produtos.
 */
Conj_Produtos converte_Produtos(Conj_Produtos lista, Cat_Produtos products, char letra);

/**
 * Inicializa um conjunto de produtos.
 * @param int capacidade.
 * @return Conj_Produtos.
 */
Conj_Produtos init_Conjunto(int capacidade);

/**
 * Prepara os dados para serem apresentados.
 * @param Conj_Produtos conjunto.
 * @return Conj_Produtos.
 */
void apresenta_Produtos(Conj_Produtos conjunto);

#endif