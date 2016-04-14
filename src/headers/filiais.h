#ifndef _filiais_h_
#define _filiais_h_

#include "catalogo.h"
#include "produtos.h"
#include "clientes.h"
#include "venda.h"
#include "global.h"

typedef struct filial *Filial;
typedef struct conjunto_filiais *Conj_Filiais;

Filial init_Filial();
Filial cria_Dados_Filial(Filial filial, Cat_Produtos produtos, Cat_Clientes clientes);
Filial adiciona_Venda_Filial(Filial f, Venda v);

Conj_Filiais init_Conj_Filiais(int n);
Conj_Filiais adiciona_Nome(Conj_Filiais c, char* nome);


#endif