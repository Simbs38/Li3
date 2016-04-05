#ifndef _produtos_h_
#define _produtos_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"

typedef struct catalogo_produtos *Cat_Produtos;
typedef char* Produto;
typedef struct prod *Produtos;

Cat_Produtos init_cat_produtos();
Cat_Produtos insere_produto(Cat_Produtos products, Produto prod);
Boolean existe_Produto(Cat_Produtos products, Produto product);
int total_Produtos(Cat_Produtos products);
void remove_Catalogo_Produtos(Cat_Produtos products);
int total_Produtos_letra(Cat_Produtos products, char letra);

#endif