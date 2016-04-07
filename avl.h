#ifndef _avl_h_
#define _avl_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef void* Estrutura;
typedef char* Valor;
typedef struct nodeAVL* AVL;
typedef int Boolean;

#define true 1
#define false 0

AVL initAVL();
AVL avl_insert(AVL node, Valor string, Estrutura estrutura);
Boolean avl_lookUp(AVL node, Valor value);
int avl_count(AVL node);
void avl_free(AVL node);
AVL avl_clone(AVL node);
void* avl_getEstrutura(AVL node, Valor value);
void preOrder(AVL root);

#endif