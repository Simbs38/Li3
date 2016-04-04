#ifndef _leituras_h_
#define _leituras_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"
#include "produtos.h"
#include "clientes.h"

#define MAXBUFFERPRODUTOS  64
#define MAXBUFFERCLIENTES 32

void leitura_ficheiros(Cat_Clientes costumers, Cat_Produtos products);

#endif