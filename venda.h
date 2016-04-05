#ifndef _venda_h_
#define _venda_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "catalogo.h"
#include "clientes.h"
#include "produtos.h"

typedef struct venda *Venda;

Venda initVenda();
Venda record_sale(char* product, double price, int quantity, char promotion, char* client, int month, int shop);
void change_sale(Venda sale, char* product, double price, int quantity, char promotion, char* client, int month, int shop);
Produto getProduto (Venda sale);
Cliente getCliente (Venda sale);

#endif