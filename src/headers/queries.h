#ifndef _queries_h_
#define _queries_h_

#include "avl.h"
#include "produtos.h"
#include "clientes.h"
#include "faturacao.h"
#include "filiais.h"
#include "global.h"

int querie_1(Cat_Produtos produtos,Cat_Clientes clientes,Faturacao faturas,Filial filiais[], int modo);
int querie_2(Cat_Produtos produtos);
int querie_3(Faturacao faturas);
int querie_4(Faturacao faturas);
int querie_6(Faturacao faturas);
void apresenta_Lista(Lista list);

#endif