#ifndef _array_dinamico_
#define _array_dinamico_

#include "avl.h"

typedef struct lista *Lista;


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

/**
 * Retorna um Boolean referente a um elemento se encontrar na lista ou não.
 * @param list Lista (array dinâmico).
 * @param valor char* a verificar a existência.
 * @return Boolean.
 */
Boolean existe_Lista(Lista list, char* valor);


Lista clientes_compraram_filial(Lista list,AVL tree);

int lista_nr_elementos_diferentes(Lista a, Lista b);


#endif