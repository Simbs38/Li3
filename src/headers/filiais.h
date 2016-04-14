#ifndef _filiais_h_
#define _filiais_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "produtos.h"
#include "clientes.h"
#include "avl.h"
#include "catalogo.h"
#include "venda.h"




typedef int *Array_int;
typedef struct info *INFO_FILIAL;
typedef struct conjunto_filiais *Conj_Filiais;
typedef struct produtosNode *ProdutosNode;
typedef struct clientesNode *ClientesNode;
typedef struct clientes_Produto_Node *Clientes_Produto_Node;
typedef struct produtos_Cliente_Node *Produtos_Cliente_Node;
typedef struct info_final *Info_Final;


INFO_FILIAL full_init();
INFO_FILIAL init_info_filial();
ProdutosNode init_infoprod();
ClientesNode init_infocli();
Info_Final init_infolast(Venda sale);
Info_Final insere_final_estrutura(INFO_FILIAL inf, Venda sale,ClientesNode nodecli,ProdutosNode nodepro);
Info_Final update_infolast(Venda sale, Info_Final final);
INFO_FILIAL insere_produto_estrutura(INFO_FILIAL inf, Venda sale, Info_Final final,ProdutosNode node);
INFO_FILIAL insere_cliente_estrutura(INFO_FILIAL inf, Venda sale, Info_Final final,ClientesNode node);
INFO_FILIAL insere_compra(INFO_FILIAL inf,Venda sale);
INFO_FILIAL init_filiais();
int getprodutosComprados(INFO_FILIAL info,char *cliente,int mes,int filiais);
Boolean info_lookUp(INFO_FILIAL info,char *string,int n);
int getnotprodutos(INFO_FILIAL info,int lim);
int getnotclientes(INFO_FILIAL info,int lim);
Boolean nexisteproduto(ProdutosNode pro); 
Boolean nexistecliente(ClientesNode cli);

#endif