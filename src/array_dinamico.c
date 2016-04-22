#include "./headers/array_dinamico.h"

#include <stdlib.h>
#include <string.h>

#define ELEMENTOS_PAGINA 20

struct lista {
    char** array;
    int pos;
    int capacidade;
};

struct pagina {
    Lista array_dinamico;
    int nr_pagina;
    int total_paginas;
    int tamanho_pagina;
    int nr_elementos;
    int total_elementos;
};

static Lista converte_aux(Lista list, NODO tree);
static Lista produtos_nao_comprados_totais_aux(Lista list, NODO tree);
static Lista clientes_compraram_filial_aux(Lista list, NODO tree);


Lista init_Lista(int size) {
    Lista conjunto = (Lista) malloc(sizeof(struct lista));
    conjunto->array = (char**) malloc(size *sizeof(char*));
    conjunto->pos = 0;
    conjunto->capacidade = size;
    return conjunto;
}


Lista lista_insert(Lista conjunto ,char* valor) {
    
    int posicao = conjunto->pos;
    
    if(conjunto->pos == (conjunto->capacidade - 2)) {
        conjunto->capacidade *= 2;
        conjunto->array = realloc(conjunto->array,conjunto->capacidade *sizeof(char *));
    }

    conjunto->array[posicao] = malloc((strlen(valor)+1)*sizeof(char));
    strcpy(conjunto->array[posicao],valor); 
    conjunto->pos++;

    return conjunto;
}


Lista lista_converte(Lista list, AVL tree) {
    NODO n = getNodo(tree);
    list = converte_aux(list,n);
    return list;
}


static Lista converte_aux(Lista list, NODO tree) {
    if(tree != NULL) {
        char* nome = getString(tree);
        list = converte_aux(list,getNodoEsq(tree));
        list = lista_insert(list,nome);
        list = converte_aux(list,getNodoDir(tree));   
        free_Nodo(tree);
        free(nome);
    }
    return list;
}


Lista produtos_nao_comprados_totais(Lista list,AVL tree) {
    list = produtos_nao_comprados_totais_aux(list,getNodo(tree));
    return list;
}

static Lista produtos_nao_comprados_totais_aux(Lista list, NODO tree) {
    if(tree!=NULL) {
        list = produtos_nao_comprados_totais_aux(list,getNodoEsq(tree));
        if(getCont(tree) == NULL) list = lista_insert(list,getString(tree));
        list = produtos_nao_comprados_totais_aux(list,getNodoDir(tree));  
    }
    return list;
}


Boolean existe_Lista(Lista list, char* valor) {
    int i;
    for(i = 0; i < list->pos; i++) {
        if(strcmp(list->array[i],valor) == 0) return true;
    }
    return false;
}

void free_Lista(Lista list) {
    int i;
    for(i = 0; i < list->pos; i++) {
        free(list->array[i]);
    }
    free(list->array);
    free(list);
}


int lista_getPos(Lista list) {
    return list->pos;
}


char* lista_getNome(Lista list, int pos) {
    char* novo = malloc((strlen(list->array[pos])+1)*sizeof(char));
    strcpy(novo,list->array[pos]);
    return novo;
}



Lista clientes_compraram_filial(Lista list,AVL tree) {
    NODO x = getNodo(tree);
    list = clientes_compraram_filial_aux(list,x);
    return list;
}


static Lista clientes_compraram_filial_aux(Lista list, NODO tree) {
    if(tree!=NULL) {
        list = clientes_compraram_filial_aux(list,getNodoEsq(tree));
        if(getCont(tree) != NULL) list = lista_insert(list,getString(tree));
        list = clientes_compraram_filial_aux(list,getNodoDir(tree));  
    }
    return list;
}


int lista_nr_elementos_diferentes(Lista a, Lista b) {
    int i, resultado = 0;
    for(i = 0; i < b->pos; i++) {
        if(existe_Lista(a,b->array[i]) == false) resultado++; 
    }
    resultado += a->pos;
    
    return resultado;
}


Pagina init_Pagina(int capacidade) {
    
    Pagina nova = (Pagina) malloc(sizeof(struct pagina));
    nova->array_dinamico = NULL;
    nova->nr_pagina = 0;
    nova->total_paginas = 0;
    nova->tamanho_pagina = capacidade;
    nova->nr_elementos = 0;
    nova->total_elementos = 0;
    
    return nova;
}


void free_Pagina(Pagina p) {
    free_Lista(p->array_dinamico);
    free(p);
}


int getNrPagina(Pagina p) {
    return p->nr_pagina;
}


int getNrElementosPag(Pagina p) {
    return p->nr_elementos;
}


int getNrElementosTotal(Pagina p) {
    return p->total_elementos;
}


int getNrPaginaTotal(Pagina p) {
    return p->total_paginas;
}


char* getStringPagina(Pagina p, int posicao) {
    return lista_getNome(p->array_dinamico,posicao);
}


Pagina getPagina(Pagina p, Lista l, int pagina) {

    int i;
    int last_pagina = l->pos % p->tamanho_pagina;
    p->total_elementos = l->pos;
    p->total_paginas = (last_pagina == 0) ? (l->pos / p->tamanho_pagina) : ((l->pos / p->tamanho_pagina) + 1);
    p->array_dinamico = init_Lista(p->tamanho_pagina);
    p->nr_pagina = pagina;

    for(i = (pagina-1) * p->tamanho_pagina; i < (pagina * p->tamanho_pagina) && (i < p->total_elementos); i++) {
        lista_insert(p->array_dinamico,l->array[i]);
    }

    p->nr_elementos = p->array_dinamico->pos;

    return p;
}