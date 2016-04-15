/**
 * @file avl.h
 * @brief Ficheiro que contem a API relativa á implementação de AVL's.
 */

#ifndef _avl_h_
#define _avl_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"


typedef struct heap* Heap;

typedef struct heapNode *HeapNode;

/*quantidade produto custo */


/**
 * Inicia uma nova AVL.
 * @return Nova AVL nula
 */
Heap initHeap();

/**
 * Insere na arvore tree tendo como referência de posicionamento um char*.
 * @param tree AVL onde insere.
 * @param key char* a inserir.
 * @param estrutura Conteúdo/Estrutura a inserir.
 * @return AVL com o novo nodo adicionado.
 */
Heap heap_push(Heap heap,char *produto,int quantidade, float custo);

char *heap_pop(Heap heap);

Heap heap_join(Heap heap1,Heap heap2);

/**
 * Executa um clone de uma dada AVL.
 * @param node AVL a clonar.
 * @return AVL nova, clonada da anterior.
 */
Heap heap_clone(Heap heap);

/**
 * Devolve um Boolean referente a ter encontrado ou não na AVL o Valor value.
 * @param tree AVL onde é efectuada a procura.
 * @param value valor a procurar na AVL.
 * @return Boolean com o resultado.
 */
Boolean heap_look(Heap heap,char *produto);

/**
 * Devolve o tamanho (quantidade de nodos) de uma AVL passada como argumento.
 * @param tree AVL da qual se pretende o tamanho.
 * @return Int com tamanho da AVL.
 */
int heap_count(Heap heap);

/**
 * Função com o objetivo de limpar da memória uma dada AVL.
 * @param nodo AVL a limpar da memória.
 */
void heap_free(Heap heap);

#endif /* _avl_h_ */