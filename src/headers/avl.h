#ifndef _avl_h_
#define _avl_h_

#include <stdlib.h>
#include <string.h>
#include "global.h"


typedef struct nodeAVL* NODO;
typedef struct avl* AVL;

typedef struct lista *Lista;

typedef void* Estrutura;
typedef char* Valor;


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
Lista lista_insert(Lista conjunto ,char* valor);
Lista produtos_nao_comprados_totais(Lista list,AVL tree);
int lista_getPos(Lista list);
char* lista_getNome(Lista list, int pos);

#endif