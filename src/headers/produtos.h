#ifndef _produtos_h_
#define _produtos_h_

#include <string.h>
#include <stdlib.h>

#include "catalogo.h"
#include "global.h"

typedef struct catalogo_produtos *Cat_Produtos;
typedef struct produto *Produto;
typedef struct conjunto_produtos *Conj_Produtos;

Cat_Produtos init_cat_produtos();
Cat_Produtos insere_produto(Cat_Produtos products, Produto prod);
Cat_Produtos clone_Catalogo_Produtos(Cat_Produtos products);
Catalogo get_Catalogo(Cat_Produtos products);
Boolean existe_Produto(Cat_Produtos products, Produto product);
int total_Produtos(Cat_Produtos products);
int total_Produtos_letra(Cat_Produtos products, char letra);
void remove_Catalogo_Produtos(Cat_Produtos products);

Produto criaProduto();
void alteraProduto(Produto product, char *info);
char* getNomeProduto(Produto product);
void free_produto(Produto product);

Conj_Produtos converte_Produtos(Conj_Produtos lista, Cat_Produtos products, char letra);
Conj_Produtos init_Conjunto(int capacidade);
void apresenta_Produtos(Conj_Produtos conjunto);

#endif