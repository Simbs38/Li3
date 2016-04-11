#ifndef _avl_h_
#define _avl_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "global.h"

typedef struct nodeAVL* NODO;
typedef struct avl* AVL;

typedef void* Estrutura;
typedef char* Valor;

typedef struct lista *Lista;

/*******
AVL
*****/

AVL initAVL();
AVL avl_insert(AVL arvore, Valor key, Estrutura estrutura);
AVL avl_clone(AVL node);

Boolean avl_lookUp(AVL tree, Valor value);
int avl_count(AVL tree);
void avl_free(AVL node);

Estrutura avl_getEstrutura(AVL node, Valor value);


/*********
ARRAY
********/

Lista init_Lista(int capacidade);
Lista lista_converte(Lista list, AVL tree);
void apresenta_Lista(Lista list);
Lista lista_insert(Lista conjunto ,char* valor);
Lista produtos_nao_comprados_totais(Lista list,AVL tree);

#endif