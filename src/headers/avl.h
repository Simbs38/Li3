#ifndef _avl_h_
#define _avl_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodeAVL* NODO;
typedef struct avl* AVL;

typedef void* Estrutura;
typedef char* Valor;
typedef int Boolean;

#define true 1
#define false 0


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


#endif