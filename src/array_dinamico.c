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
    int nr_de_paginas;
    int tamanho_pagina;
    int nr_elementos;
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

    conjunto->array[posicao] = malloc(10);
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
        list = converte_aux(list,getNodoEsq(tree));
        list = lista_insert(list,getString(tree));
        list = converte_aux(list,getNodoDir(tree));   
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
    char* novo = malloc(strlen(list->array[pos])+1);
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



Pagina init_Pagina(Lista l, int capacidade) {
    int last_pagina = l->pos % capacidade;
    Pagina nova = (Pagina) malloc(sizeof(struct pagina));
    nova->array_dinamico = init_Lista(capacidade);
    nova->nr_pagina = 0;
    nova->nr_de_paginas = (last_pagina == 0) ? (l->pos / capacidade) : ((l->pos / capacidade) + 1);
    nova->tamanho_pagina = capacidade;
    nova->nr_elementos = l->pos;
    return nova;
}


void free_Pagina(Pagina p) {
    free_Lista(p->array_dinamico);
    free(p);
}

/*
Pagina getPagina(Pagina p, Lista l, int pagina) {
    p->nr_pagina = pagina;
    
    for(i = (pagina-1) * p->tamanho_pagina; i < (pagina * p->tamanho_pagina) && i < p->nr_elementos; i++) {
        printf("\t%d\t%s\n",i+1,lista_getNome(list,i));
    }
    
    return p;
}
*/