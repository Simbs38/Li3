#ifndef _venda_h_
#define _venda_h_

#include <string.h>
#include <stdlib.h>

#include "clientes.h"
#include "produtos.h"

typedef struct venda *Venda;

Venda initVenda();
Venda record_sale(char* product, double price, int quantity, char promotion, char* client, int month, int shop);
void change_sale(Venda sale, char* product, double price, int quantity, char promotion, char* client, int month, int shop);
Produto getProduto (Venda sale);
Cliente getCliente (Venda sale);
int getMes(Venda sale);
int getFilial(Venda sale);
int getQuantidade(Venda sale);
char getPromocao(Venda sale);
double getPreco(Venda sale);
Boolean validate_sale(Cat_Produtos products, Cat_Clientes costumers, Venda venda);


#endif