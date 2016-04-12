#ifndef _catalogo_h_
#define _catalogo_h_

#include "avl.h"
#include "global.h"

typedef struct catalogo *Catalogo;
typedef struct array_catalogo *Array;

Catalogo init_Catalogo();
Catalogo insere_Catalogo(Catalogo catalogo, char* key, void* estrutura);
Catalogo clone_Catalogo(Catalogo catalogo);
void remove_Catalogo(Catalogo catalogo);
Boolean existe_Catalogo(Catalogo catalogo, char* key);
int total_elems_Catalogo(Catalogo catalogo);
int total_elems_letra(Catalogo catalogo, char letra);
void* getEstrutura_Catalogo(Catalogo catalogo, char* key);

Array init_Array(int capacidade);
Array lista_catalogo_letra(Array lista,Catalogo catalogo, char letra);
Array adiciona_array(Array lista, char* info);
Array catalogo_produtos_nao_comprados_totais(Array lista, Catalogo catalogo);
Array catalogo_lista_total(Array lista,Catalogo catalogo);
void apresenta_Array(Array lista);
char* catalogo_getElemento(Array lista, int pos);
int catalogo_getPos(Array lista);

#endif