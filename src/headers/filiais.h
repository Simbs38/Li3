#ifndef _filiais_h_
#define _filiais_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"
#include "catalogo.h"
#include "venda.h"





typedef struct info *INFO_FILIAL;

typedef struct produtosNode *ProdutosNode;
typedef struct clientesNode *ClientesNode;
typedef struct clientes_Produto_Node *Clientes_Produto_Node;
typedef struct produtos_Cliente_Node *Produtos_Cliente_Node;
typedef struct info_final *Info_Final;


INFO_FILIAL full_init(Venda  sale);
INFO_FILIAL init_info_filial();
ProdutosNode init_infoprod();
ClientesNode init_infocli();
Clientes_Produto_Node init_infoCliInProd();
Produtos_Cliente_Node init_infoProdInCli();
Info_Final init_infolast(Venda sale);
INFO_FILIAL full_init(Venda  sale);
Info_Final update_infolast(Venda sale);
INFO_FILIAL insere_produto_estrutura(INFO_FILIAL inf, Venda sale);
INFO_FILIAL insere_cliente_estrutura(INFO_FILIAL inf, Venda sale);
INFO_FILIAL insere_compra(INFO_FILIAL inf,Venda sale);


#endif