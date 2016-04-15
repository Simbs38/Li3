#ifndef _venda_h_
#define _venda_h_

#include "clientes.h"
#include "produtos.h"
#include "global.h"

typedef struct venda *Venda;

/**
 * Inicializa a estrutura venda.
 * @return Venda.
 */
Venda initVenda();

/**
 * Atualiza uma venda na estrutura.
 * @param char * product.
 * @param double price.
 * @param int quantity.
 * @param char promotion.
 * @param char *client.
 * @param int month.
 * @param int shop
 * @return Venda.
 */
void change_sale(Venda sale, char* product, double price, int quantity, char promotion, char* client, int month, int shop);

/**
 * Devolve o codigo do produto de uma venda.
 * @param Venda sale
 * @return Produto.
 */
Produto getProduto (Venda sale);

/**
 * Devolve o codigo do cliente de uma venda.
 * @param Venda sale
 * @return Produto.
 */
Cliente getCliente (Venda sale);

/**
 * Devolve o mês do produto de uma venda.
 * @param Venda sale
 * @return int.
 */
int getMes(Venda sale);

/**
 * Devolve uma filiail.
 * @param Venda sale
 * @return int.
 */
int getFilial(Venda sale);

/**
 * Devolve a quantidade de um produto.
 * @param Venda sale
 * @return int.
 */
int getQuantidade(Venda sale);

/**
 * Devolve se a venda foi efetuada em P ou N.
 * @param Venda sale
 * @return char.
 */
char getPromocao(Venda sale);

/**
 * Devolve o preço do produto de uma venda.
 * @param Venda sale
 * @return double.
 */
double getPreco(Venda sale);

/**
 * Valida a compra verificando todos os seus componentes.
 * @param Cat_Produtos products.
 * @param Cat_Clientes costumers.
 * @param Venda venda.
 * @return Boolean com valor de verdade.
 */
Boolean validate_sale(Cat_Produtos products, Cat_Clientes costumers, Venda venda);

#endif