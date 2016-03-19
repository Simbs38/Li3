#ifndef _valida_h_
#define _valida_h_

#include "main.h"
#include "avl.h"

int valida_vendas(CATALOG produtos, CATALOG clientes,struct venda *vendas[1000000]);
void insert_sale(struct venda *vendas, char* product,double preco,int quantidade, char tipo, char* client, int mes , int filial);

#endif