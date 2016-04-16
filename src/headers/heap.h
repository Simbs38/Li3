/**
 * @file heap.h
 * @brief Ficheiro que contem a API relativa á implementação de Heap's.
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
 * Insere na Heap tendo como referência a quantidade de um produto.
 * @param heap Heap onde insere.
 * @param produto char *.
 * @param quantidade int.
 * @param custo float.
 * @return Heap com o novo membro adicionado.
 */
Heap heap_push(Heap heap,char *produto,int quantidade, float custo);


/**
 * Devolve o produto com maior quantidade.
 * @param heap Heap com todos os produtos.
 * @return char * com o nome do produto.
 */
char *heap_pop(Heap heap);

Heap bubbleUp(Heap heap,int i);
Heap bubbleDown(Heap heap,int n);
Heap swap(Heap heap,int n1,int n2);

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