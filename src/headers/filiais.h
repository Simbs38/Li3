#ifndef _filiais_h_
#define _filiais_h_


#include "catalogo.h"
#include "produtos.h"
#include "clientes.h"
#include "venda.h"
#include "global.h"

typedef struct filial *Filial;
typedef struct conjunto_filiais *Conj_Filiais;
typedef struct nodo_produtos *Nodo_Produtos;


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
 * Inicia um Nodo de produtos.
 * @return Nodo_Produtos.
 */
Nodo_Produtos init_Nodo_Produtos();

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

#endif