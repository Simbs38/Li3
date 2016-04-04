#ifndef _produtos_h_
#define _produtos_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"

#define MAXBUFFERProducts  64


typedef struct catalogo_produtos *Cat_Produtos;
typedef char* Produto;
typedef AVL Produtos;


Cat_Produtos init_cat_produtos();
Cat_Produtos insere_produto(Cat_Produtos products, Produto prod);
int verify_exist_product(Cat_Produtos products, Produto product);
void imprime(Cat_Produtos products, int index);


#endif