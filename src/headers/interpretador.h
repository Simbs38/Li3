#ifndef _interpretador_h_
#define _interpretador_h_

#include "produtos.h"
#include "clientes.h"
#include "faturacao.h"
#include "filiais.h"
#include "global.h"

int menu_principal(Cat_Produtos produtos, Cat_Clientes clientes, Faturacao faturas,Filial filiais[],int estado);

#endif
