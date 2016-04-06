#ifndef _produtos_h_
#define _produtos_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "avl.h"
#include "catalogo.h"

#define MAXSIZEPRODUTOS 64


typedef struct catalogo_produtos *Cat_Produtos;
typedef struct produto *Produto;

Produto criaProduto(char* info);
void alteraProduto(Produto product, char *info);
Cat_Produtos init_cat_produtos();
Cat_Produtos insere_produto(Cat_Produtos products, Produto prod);
Boolean existe_Produto(Cat_Produtos products, Produto product);
int total_Produtos(Cat_Produtos products);
void remove_Catalogo_Produtos(Cat_Produtos products);
int total_Produtos_letra(Cat_Produtos products, char letra);
Cat_Produtos clone_Catalogo_Produtos(Cat_Produtos products);
char* getNomeProduto(Produto product);
Catalogo get_Catalogo(Cat_Produtos products);

#endif