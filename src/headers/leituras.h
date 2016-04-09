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

#define MAXBUFFERCLIENTES 32
#define MAXBUFFERPRODUTOS 64
#define MAXBUFFERVENDAS 128

void leitura_ficheiros(int argc, char** argv, Cat_Clientes costumers, Cat_Produtos products, Faturacao contas);

#endif