#ifndef _catalogo_h_
#define _catalogo_h_

#include "avl.h"

typedef struct catalogo *Catalogo;

Catalogo init_Catalogo();
Boolean existe_Catalogo(Catalogo catalogo, char* key);
Catalogo insere_Catalogo(Catalogo catalogo, char* key);
int total_elems_Catalogo(Catalogo catalogo);
int total_elems_letra(Catalogo catalogo, char letra);
void remove_Catalogo(Catalogo catalogo);

#endif