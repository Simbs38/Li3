#ifndef _queries_h_
#define _queries_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "produtos.h"
#include "clientes.h"
#include "faturacao.h"
#include "filiais.h"
#include "global.h"

int querie_1(Cat_Produtos produtos,Cat_Clientes clientes,Faturacao faturas,INFO_FILIAL info, int modo);
int querie_2(Cat_Produtos produtos);
int querie_3(Faturacao faturas);
int querie_4(Faturacao faturas);
int querie_5(INFO_FILIAL info);
int querie_6(Faturacao faturas);
int querie_7(INFO_FILIAL info);
int querie_8(INFO_FILIAL info);
int querie_9(INFO_FILIAL info);
int querie_10(INFO_FILIAL info);
int querie_11(INFO_FILIAL info);
int querie_12(INFO_FILIAL info);
void apresenta_Lista(Lista list);

#endif