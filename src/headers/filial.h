/**
 * @file filial.h
 * @brief Ficheiro que contem a API relativa á implementação de uma Filial.
 */

#ifndef _filial_h_
#define _filial_h_

#include "global.h"
#include "venda.h"
#include "avl.h"
#include "catalogo.h"
#include "produtos.h"
#include "clientes.h"
#include "array_dinamico.h"
#include "heap.h"

typedef struct filial *Filial;
typedef struct conjunto_filiais *Conj_Filiais;
typedef struct nodo_produtos *Nodo_Produtos;
typedef struct heap_filial *HEAP;


/**
 * Adiciona dados a uma filial.
 * @param Filial filial.
 * @param Cat_Produtos produtos.
 * @param Cat_Clientes clientes.
 * @return Filial.
 */
Filial cria_Dados_Filial(Filial filial, Cat_Produtos produtos, Cat_Clientes clientes);

/**
 * Inicializa uma filial.
 * @return Filial.
 */
Filial init_Filial();

/**
 * Adiciona dados de uma venda a uma filial.
 * @param Filial f.
 * @param Venda v.
 * @return Filial.
 */
Filial adiciona_Venda_Filial(Filial f, Venda v);


/**
 * Inicia um conjunto de filiais.
 * @param int n indicativo do tamanho inicial do conjunto.
 * @return Conj_Filiais.
 */
Conj_Filiais init_Conj_Filiais(int n);

/**
 * Adiciona um nome ao array do conjuto de filiais.
 * @param Conj_Filiais c.
 * @param char *nome.
 * @return Conj_Filiais.
 */
Conj_Filiais adiciona_Nome(Conj_Filiais c, char* nome);

/**
 * Retorna o numero de unidades compradas dado um cliente e um mês.
 * @param Filial f.
 * @param char* cliente.
 * @param int mes.
 * @return int.
 */
int nr_total_unidades_compradas(Filial f, char* cliente, int mes);

/**
 * Retorna um Boolean caso um dado cliente tenha comprado algum produto.
 * @param f Filial a procurar.
 * @param valor char* a verificar.
 * @return Boolean.
 */
Boolean verifica_cliente_comprado(Filial f, char* c);


/**
 * Retorna um Boolean referente à existência de um dado cliente.
 * @param f Filial.
 * @param char* cliente a procurar.
 * @return Boolean com o resultado da procura.
 */
Boolean filial_existe_Cliente(Filial f, char* cliente);

/**
 * Retorna um Boolean referente à existência de um dado produto.
 * @param f Filial.
 * @param char* produto a procurar.
 * @return Boolean com o resultado da procura.
 */
Boolean filial_existe_Produto(Filial f,char* produto);

/**
 * Retorna o numero de unidades vendidas de um dado produto.
 * @param f Filial.
 * @param char* produto a procurar.
 * @return int com o numero de unidades vendidas.
 */
int getQuantidadeProduto(Filial f, char* produto);

/**
 * Retorna o numero de clientes de um dado produto.
 * @param f Filial.
 * @param char* produto a procurar.
 * @return int com o numero de clientes.
 */
int nr_clientes_de_um_produto(Filial f, char* produto);

/**
 * Função responsavel por apresentar um Conj_Filiais.
 * @param c Conj_Filiais a apresentar.
 */
void apresenta_Dados_Filial(Conj_Filiais c);

/**
 * Retorna o tamanho de um Conj_Filiais.
 * @param conjunto Conj_Filiais.
 * @return int com o tamanho.
 */
int filial_getPos(Conj_Filiais conjunto);

/**
 * Retorna a string de um Conj_Filiais uma posição.
 * @param conjunto Conj_Filiais.
 * @param pos posição de onde se pretende retirar a string.
 * @return char* com a string.
 */
 char* filial_get_elemento_lista(Conj_Filiais conjunto, int pos);

/**
 * Retorna o numero de elementos diferentes entre dois Conj_Filiais.
 * @param a Conj_Filiais.
 * @param b Conj_Filiais.
 * @return int com o valor pretendido.
 */
int filiais_nr_elementos_diferentes(Conj_Filiais a, Conj_Filiais b);

/**
 * Inicia uma nova HEAP.
 * @return HEAP criada.
 */
HEAP init_HEAP();


/**
 * Converte uma dada AVL com os produtos de um cliente num dado mês em HEAP para ordenação dos valores.
 * @param f Filial onde se encontram os dados.
 * @param HEAP h onde serão colocados os valores.
 * @param char* cliente com o cliente pretendido.
 * @param mes int com o mês pretendido.
 * @param ordenacao char indicando se é pretendida uma ordenação por quantidade ou faturação.
 * @return HEAP após a conversão.
 */
HEAP lista_codigos_de_clientes(Filial f, HEAP h, char* cliente, int mes, char ordenacao);

/**
 * Converte numa HEAP os dados sobre os produtos de um cliente num ano.
 * @param f Filial onde se encontram os dados.
 * @param HEAP h onde serão colocados os valores.
 * @param char* cliente com o cliente pretendido.
 * @param ordenacao char indicando se é pretendida ordenação por quantidade ou faturação.
 * @return HEAP após a conversão.
 */
HEAP top3_clientes(Filial f, HEAP h, char* cliente, char ordenacao);

/**
 * Retorna um Conj_Filiais com os 3 produtos mais comprados por um cliente, dada uma HEAP com os dados.
 * @param c Conj_Filiais onde serão colocados os valores.
 * @param h HEAP onde se encontram os dados.
 * @param ordenacao char indicando se é pretendida ordenação por quantidade ou faturação.
 * @return Conj_Filiais com os valores.
 */
Conj_Filiais lista_top3(Conj_Filiais c, HEAP h, char ordenacao);

/**
 * Retorna um Conj_Filiais com nomes armazenados numa dada HEAP.
 * @param c Conj_Filiais onde serão colocados os valores.
 * @param h HEAP onde se encontram os dados.
 * @param ordenacao char indicando se é pretendida ordenação por quantidade ou faturação.
 * @return Conj_Filiais com os valores.
 */
Conj_Filiais convert_Heap_Lista(Conj_Filiais c, HEAP h, char ordenacao);

/**
 * Converte numa HEAP os dados sobre os produtos oraganizando-os por quantidade comprada.
 * @param f Filial onde se encontram os dados.
 * @param HEAP h onde serão colocados os valores.
 * @return HEAP após a inserção dos dados.
 */
HEAP heap_produtos_mais_vendidos(Filial f, HEAP h);

/**
 * Retorna um Conj_Filiais com os N produtos mais comprados, dada uma HEAP com os dados.
 * @param c Conj_Filiais onde serão colocados os valores.
 * @param h HEAP onde se encontram os dados.
 * @param n int indicando o numero de produtos pretendidos.
 * @return Conj_Filiais com os valores.
 */
Conj_Filiais retira_N_Produtos(Conj_Filiais c, HEAP h, int n);

/**
 * Retorna um Conj_Filiais com os clientes que efetuaram compras numa dada filial.
 * @param c Conj_Filiais onde serão colocados os valores.
 * @param f Filial contendo os dados.
 * @return Conj_Filiais com os valores.
 */
Conj_Filiais lista_clientes_compraram_filial(Conj_Filiais c, Filial f);

/**
 * Retorna um Conj_Filiais com os clientes de um dado produto em modo N ou modo P.
 * @param f Filial contendo os dados.
 * @param produto char* do produto pretendido.
 * @param promo char indicando se são pretendidos valores em modo Normal ou Promoção.
 * @return Conj_Filiais com os valores.
 */
Conj_Filiais lista_clientes_de_produto(Filial f, char* produto, char promo);

#endif /* _filial_h_ */