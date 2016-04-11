#ifndef _catalogo_h_
#define _catalogo_h_

#include "avl.h"
#include "global.h"

typedef struct catalogo *Catalogo;
typedef struct array_catalogo *Array;

Catalogo init_Catalogo(int n);
Boolean existe_Catalogo(Catalogo catalogo, char* key);
Catalogo insere_Catalogo(Catalogo catalogo, char* key, void* estrutura, int index);
int total_elems_Catalogo(Catalogo catalogo);
int total_elems_letra(Catalogo catalogo, char letra);
void remove_Catalogo(Catalogo catalogo);
Catalogo clone_Catalogo(Catalogo catalogo);
void* getEstrutura_Catalogo(Catalogo catalogo, char* key,int index);



Array init_Array(int capacidade);
Array lista_catalogo(Array lista,Catalogo catalogo, char letra);
Array adiciona_array(Array lista, char* info);
Array catalogo_produtos_nao_comprados_totais(Array lista, Catalogo catalogo);
void apresenta_Array(Array lista);

#endif