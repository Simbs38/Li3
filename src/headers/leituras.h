#ifndef _leituras_h_
#define _leituras_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "produtos.h"
#include "clientes.h"
#include "venda.h"
#include "catalogo.h"
#include "faturacao.h"
#include "filiais.h"
#include "global.h"


#define MAXBUFFERCLIENTES 32
#define MAXBUFFERPRODUTOS 64
#define MAXBUFFERVENDAS 128


/**
 * Recebe as estruturas inicializadas e os ficheiros ja abertos e copia a informação dos ficheiros para as estruturas.
 * @param Cat_Clientes costumers.
 * @param Cat_Produtos products.
 * @param Faturacao contas.
 * @param Filiais filiais.
 * @param FILE *f_clients.
 * @param FILE *f_prods.
 * @param FILE* f_sales. 
 * @param char* f_cname.
 * @param char* f_pname.
 * @param char* f_vname
 * @param int estado.
 */
void leitura_ficheiros(Cat_Clientes costumers, Cat_Produtos products, Faturacao contas, Filiais filiais, FILE *f_clients, FILE *f_prods, FILE* f_sales, char* f_cname, char* f_pname, char* f_vname);

#endif