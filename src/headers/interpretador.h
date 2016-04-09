#ifndef _interpretador_h_
#define _interpretador_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "produtos.h"
#include "clientes.h"
#include "faturacao.h"

void menu_principal(Cat_Produtos produtos, Cat_Clientes clientes, Faturacao faturas);
int menu_catalogo(Cat_Produtos produtos);
int menu_faturacao(Faturacao faturas);

#endif
