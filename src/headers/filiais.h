#ifndef _filiais_h_
#define _filiais_h_


#include "catalogo.h"
#include "produtos.h"
#include "clientes.h"
#include "venda.h"
#include "global.h"

typedef struct filiais *Filiais;
typedef struct conjunto_filiais *Conj_Filiais;
typedef struct filial *Filial;
typedef struct nodo_clientes *Nodo_Clientes;
typedef struct nodo_produtos *Nodo_Produtos;
typedef struct listafi *ListaFilial; 
typedef struct listafi *ListaFi; 



Filiais init_Filiais();
Filiais adiciona_Filiais(Filiais f, Venda v);
Filiais cria_Dados_Filiais(Filiais f,Cat_Produtos produtos,Cat_Clientes clientes);


Filial cria_Dados_Filial(Filial filial, Cat_Produtos produtos, Cat_Clientes clientes);
Filial init_Filial();
Filial adiciona_Venda_Filial(Filial f, Venda v);


Nodo_Produtos init_Nodo_Produtos();

Conj_Filiais init_Conj_Filiais(int n);
Conj_Filiais adiciona_Nome(Conj_Filiais c, char* nome);

#endif