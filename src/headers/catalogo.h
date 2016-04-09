#ifndef _catalogo_h_
#define _catalogo_h_

#include "avl.h"

typedef struct catalogo *Catalogo;

Catalogo init_Catalogo(int n);
Boolean existe_Catalogo(Catalogo catalogo, char* key);
Catalogo insere_Catalogo(Catalogo catalogo, char* key, void* estrutura);
int total_elems_Catalogo(Catalogo catalogo);
int total_elems_letra(Catalogo catalogo, char letra);
void remove_Catalogo(Catalogo catalogo);
Catalogo clone_Catalogo(Catalogo catalogo);
void* getEstrutura_Catalogo(Catalogo catalogo, char* key);

Lista lista_catalogo(Lista list,Catalogo catalogo, char letra);


#endif