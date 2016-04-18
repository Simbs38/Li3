#ifndef _filiais_h_
#define _filiais_h_


#include "catalogo.h"
#include "produtos.h"
#include "clientes.h"
#include "venda.h"
#include "global.h"
#include "avl.h"
#include "heap.h"
#include "array_dinamico.h"

typedef struct filial *Filial;
typedef struct conjunto_filiais *Conj_Filiais;
typedef struct nodo_produtos *Nodo_Produtos;
typedef struct heap_filial *HEAP;


/**
 * Adiciona dados a uma filial.
 * @param Filial filial.
 * @param Cat_Produtos produtos.
 * @param Cat_Clientes clientes.
 * @return Filial.
 */
Filial cria_Dados_Filial(Filial filial, Cat_Produtos produtos, Cat_Clientes clientes);

/**
 * Inicializa uma filial.
 * @return Filial.
 */
Filial init_Filial();

/**
 * Adiciona dados de uma venda a uma filial.
 * @param Filial f.
 * @param Venda v.
 * @return Filial.
 */
Filial adiciona_Venda_Filial(Filial f, Venda v);


/**
 * Inicia um conjunto de filiais.
 * @param int n.
 * @return Conj_Filiais.
 */
Conj_Filiais init_Conj_Filiais(int n);

/**
 * Adiciona um nome ao array do conjuto de filiais.
 * @param Conj_Filiais c.
 * @param char *nome.
 * @return Conj_Filiais.
 */
Conj_Filiais adiciona_Nome(Conj_Filiais c, char* nome);

/**
 * Retorna o numero de unidades compradas dado um cliente e um mês.
 * @param Filial f.
 * @param char* cliente.
 * @param int mes.
 * @return int.
 */
int nr_total_unidades_compradas(Filial f, char* cliente, int mes);

Boolean filial_existe_Cliente(Filial f, char* cliente);

Boolean filial_existe_Produto(Filial f,char* produto);

Boolean verifica_cliente_comprado(Filial f, char* c);

Conj_Filiais lista_clientes_compraram_filial(Conj_Filiais c, Filial f);

int filial_getPos(Conj_Filiais conjunto);

char* filial_get_elemento_lista(Conj_Filiais conjunto, int pos);

Conj_Filiais lista_clientes_de_produto(Filial f, char* produto, char promo);

HEAP init_HEAP();

HEAP lista_codigos_de_clientes(Filial f, HEAP h, char* cliente, int mes, char ordenacao);

Conj_Filiais convert_Heap_Lista(Conj_Filiais c, HEAP h, char ordenacao);

void apresenta_Dados_Filial(Conj_Filiais c);

Conj_Filiais retira_N_Produtos(Conj_Filiais c, HEAP h, int n);

HEAP heap_produtos_mais_vendidos(Filial f, HEAP h);

int getQuantidadeProduto(Filial f, char* produto);

int filiais_nr_elementos_diferentes(Conj_Filiais a, Conj_Filiais b);

int nr_clientes_de_um_produto(Filial f, char* produto);

HEAP top3_clientes(Filial f, HEAP h, char* cliente, char ordenacao);

Conj_Filiais lista_top3(Conj_Filiais c, HEAP h, char ordenacao);

#endif