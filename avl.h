#ifndef _avl_h_
#define _avl_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef char* Valor;
typedef struct nodeAVL* AVL;

AVL initAVL();
AVL avl_insert(AVL node, Valor string, void *estrutura);
int avl_lookUp(AVL node, Valor value);
void preOrder(AVL root);

#endif