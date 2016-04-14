#ifndef _leituras_h_
#define _leituras_h_

#include "produtos.h"
#include "clientes.h"
#include "venda.h"
#include "catalogo.h"
#include "faturacao.h"
#include "filiais.h"
#include "global.h"

void leitura_ficheiros(Cat_Clientes costumers, Cat_Produtos products, Faturacao contas, Filial filiais[], FILE *f_clients, FILE *f_prods, FILE* f_sales, char* f_cname, char* f_pname, char* f_vname);

#endif