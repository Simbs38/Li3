#ifndef _faturacao_h_
#define _faturacao_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "clientes.h"
#include "produtos.h"
#include "avl.h"
#include "venda.h"
#include "catalogo.h"

typedef struct fatura_produto *Fatura_Produto;
typedef struct faturacao *Faturacao;

Faturacao init_Faturacao();
Faturacao cria_Dados_Faturacao(Faturacao fact, Cat_Produtos);

#endif