#ifndef _catalogo_h_
#define _catalogo_h_

#include "avl.h"
#include "global.h"

typedef struct catalogo *Catalogo;
typedef struct array_catalogo *Array;


/**
 * Inicializa um Catalogo returnando o mesmo.
 * @return Catalogo inicializado.
 */
Catalogo init_Catalogo();

/**
 * Insere uma estrutura num nodo do Catalogo returnando o catalogo.
 * @param Catalogo catalogo.
 * @param key char* a procurar.
 * @param  void* estrutura estrutura a inserir no nodo.
 * @param ind index, indice onde procurar no catalogo.
 * @return Boolean com valor verdadeiro ou falso.
 */
Catalogo insere_Catalogo(Catalogo catalogo, char* key, void* estrutura);

/**
 * Cria um clone do catalogo dado, devolvendo uma copia deste.
 * @param Catalogo catalogo.
 * @return Catalogo catalogo.
 */
Catalogo clone_Catalogo(Catalogo catalogo);

/**
 * Liberta o espaço alocado na memoria para o catalogo.
 * @param Catalogo catalogo.
 */
void remove_Catalogo(Catalogo catalogo);

/**
 * Verifica um valor existe no Catalogo returnando verdadeiro se existir e false caso contrario.
 * @param Catalogo catalogo.
 * @param key char* a procurar.
 * @param ind index, indice onde procurar no catalogo.
 * @return Boolean com valor verdadeiro ou falso.
 */
Boolean existe_Catalogo(Catalogo catalogo, char* key);

/**
 * Devolve o numero de nodos do catalogo.
 * @param Catalogo catalogo.
 * @return int.
 */
int total_elems_Catalogo(Catalogo catalogo);

/**
 * Devolve o numero de nodos do catalogo começados pela letra dada.
 * @param char letra.
 * @param Catalogo catalogo.
 * @return int.
 */
int total_elems_letra(Catalogo catalogo, char letra);

/**
 * Devolve o numero de nodos do catalogo.
 * @param Catalogo catalogo.
 * @return int.
 */
void* getEstrutura_Catalogo(Catalogo catalogo, char* key);

/**
 * Inicializa um array com a capacidade indicada.
 * @param int capacidade.
 * @return Array.
 */
Array init_Array(int capacidade);

/**
 * Converte uma parte de um catalogo para uma lista
 * @param Array lista que irá receber os dados.
 * @param Catalogo catalogo.
 * @param char letra, letra que indicara ao catalogo que elementos iram ser convertidos para a lista.
 * @return Array.
 */
Array lista_catalogo_letra(Array lista,Catalogo catalogo, char letra);

/**
 * Adiciona um elemento a uma Lista.
 * @param Array lista que irá receber os dados.
 * @param char *info palavra adicionada a Lista.
 * @return Array.
 */
Array adiciona_array(Array lista, char* info);

/**
 * Retorna um array com todos os produtos não comprados.
 * @param Array lista onde serão alocados os dados.
 * @param Catalogo catalogo de onde se iram buscar os dados.
 * @return Array.
 */
Array catalogo_produtos_nao_comprados_totais(Array lista, Catalogo catalogo);

/**
 * Converte catalogo para lista??????????????????????????????????????????????????????????????????????????????????????????
 * @param Array lista.
 * @param Catalogo catalogo.
 * @return Array.
 */
Array catalogo_lista_total(Array lista,Catalogo catalogo);

/**
 * Função responsavel de apresentar um Array.
 * @param Array lista de onde serão acedidos os dados.
 */
void apresenta_Array(Array lista);

/**
 * Devolve um elemento de uma lista na posição indicada
 * @param Array lista.
 * @param int pos, posição indicada pelo utilizador.
 * @return char *.
 */
char* catalogo_getElemento(Array lista, int pos);

/**
 * Devolve o numero de posições atuais na alocadas na lista
 * @param Array lista.
 * @return int.
 */
int catalogo_getPos(Array lista);

#endif