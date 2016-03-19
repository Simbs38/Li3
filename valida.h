#ifndef _valida_h_
#define _valida_h_

#include "main.h"
#include "avl.h"

int valida_vendas(CATALOG products, CATALOG costumers, struct sale *sales[1000000]);
struct sale* insert_sale(struct sale *sales, char* product, double price, int ammount, char type, char* client, int month , int shop);

#endif