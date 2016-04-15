#ifndef _avl_h_
#define _avl_h_

#include <stdlib.h>
#include <string.h>
#include "global.h"


typedef struct nodeAVL* NODO;
typedef struct avl* AVL;

typedef struct lista *Lista;

typedef void* Estrutura;
typedef char* Valor;


/*******
AVL
*****/


/**
 * Inicia uma nova AVL.
 * @return Nova AVL nula
 */
AVL initAVL();

/**
 * Insere na arvore tree tendo como referência de posicionamento um char*.
 * @param tree AVL onde insere.
 * @param key char* a inserir.
 * @param estrutura Conteúdo/Estrutura a inserir.
 * @return AVL com o novo nodo adicionado.
 */
AVL avl_insert(AVL arvore, Valor key, Estrutura estrutura);

/**
 * Executa um clone de uma dada AVL.
 * @param node AVL a clonar.
 * @return AVL nova, clonada da anterior.
 */
AVL avl_clone(AVL node);

/**
 * Devolve um Boolean referente a ter encontrado ou não na AVL o Valor value.
 * @param tree AVL onde é efectuada a procura.
 * @param value valor a procurar na AVL.
 * @return Boolean com o resultado.
 */
Boolean avl_lookUp(AVL tree, Valor value);

/**
 * Devolve o tamanho (quantidade de nodos) de uma AVL passada como argumento.
 * @param tree AVL da qual se pretende o tamanho.
 * @return Int com tamanho da AVL.
 */
int avl_count(AVL tree);

/**
 * Função com o objetivo de limpar da memória uma dada AVL.
 * @param nodo AVL a limpar da memória.
 */
void avl_free(AVL node);

/**
 * Devolve a estrutura associada a um nodo de uma AVL passada como argumento.
 * @param node AVL de onde será devolvida a estrutura.
 * @param value char* indicando o nodo a procurar onde estará a estrutura associada.
 * @return void* com apontador para a estrutura ou NULL caso a mesma nao se encontre lá.
 */
Estrutura avl_getEstrutura(AVL node, Valor value);


/*********
ARRAY
********/

/**
 * Inicia um novo array dinâmico.
 * @param size inteiro que determina a capacidade inicial do array dinâmico.
 * @return conjunto array dinâmico
 */
Lista init_Lista(int capacidade);


/**
 * Retorna uma lista resultante da conversão para lista de uma AVL dada.
 * @param list Lista (array dinâmico) onde serão inseridos os valores.
 * @param tree AVL de onde provêm os valores a colocar na Lista.
 * @return list.
 */
Lista lista_converte(Lista list, AVL tree);

/**
 * Adiciona um char* passado como argumento no array dinâmico.
 * @param conjunto Lista (array dinâmico) onde será inserido o valor pretendido.
 * @param valor char* a colocar na Lista.
 * @return conjunto array dinâmico após a inserção.
 */
Lista lista_insert(Lista conjunto ,char* valor);


/**
 * Retorna uma Lista com os nomes dos produtos não comprados em nenhuma filial.
 * @param conjunto Lista (array dinâmico) a inserir valores.
 * @param tree AVL a procurar os valores.
 * @return conjunto array dinâmico após a inserção.
 */
Lista produtos_nao_comprados_totais(Lista list,AVL tree);


/**
 * Retorna o campo Pos da estrutura Lista.
 * @param list Lista (array dinâmico).
 * @return int tamanho do array dinâmico.
 */
int lista_getPos(Lista list);

/**
 * Retorna o valor do array dinamico dada uma posição.
 * @param list Lista (array dinâmico).
 * @param pos posição de onde se pretende retirar o valor.
 * @return char* com o valor.
 */
char* lista_getNome(Lista list, int pos);

#endif