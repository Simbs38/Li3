#ifndef _faturacao_h_
#define _faturacao_h_

#include <stdlib.h>

#include "produtos.h"
#include "venda.h"
#include "catalogo.h"
#include "global.h"

typedef struct fatura_produto *Fatura_Produto;
typedef struct faturacao *Faturacao;
typedef struct conjunto_faturas *Conj_Faturas;


/**
 * Inicializa a estrutura Faturacao.
 * @return Faturacao.
 */
Faturacao init_Faturacao();

/**
 * Insere os dados dos produtos na estrutura.
 * @param Faturacao fat.
 * @param Cat_Produtos prods.
 * @return Faturacao.
 */
Faturacao cria_Dados_Faturacao(Faturacao fact, Cat_Produtos);

/**
 * Adiciona uma venda a faturação total.
 * @param Faturacao contas
 * @param Venda venda
 * @return Faturacao.
 */
Faturacao adiciona_Fatura(Faturacao contas, Venda venda);

/**
 * Liberta o espaço alocado em memoria para a estrutura.
 * @param Faturacao fatutacao.
 */
void free_Faturacao(Faturacao faturacao);

/**
 * Inicializa as faturações de um produto.
 * @return Fatura_Produto.
 */
Fatura_Produto init_Fatura_Produto();

/**
 * Devolve a estrutura alocada junto de um produto.
 * @param Faturacao faturacao.
 * @param char* produto.
 * @return void *.
 */
void* getEstrutura_Faturacao(Faturacao faturacao, char* produto);

/**
 * Devolve o custo total de um produto num dado mês e numa dada filial em promoção ou em preço normal.
 * @param Faturacao fatura.
 * @param char* produto.
 * @param int mes.
 * @param char modo.
 * @param int filial.
 * @return int.
 */
double get_total_precos_mes_produto_filial(Faturacao fatura, char* produto, int mes, char modo, int filial);

/**
 * Devolve a quantidade total de um produto num dado mês e numa dada filial em promoção ou em preço normal.
 * @param Faturacao fatura.
 * @param char* produto.
 * @param int mes.
 * @param char modo.
 * @param int filial.
 * @return int.
 */
int get_total_quantidades_mes_produto_filial(Faturacao fatura, char* produto, int mes, char modo, int filial);

/**
 * Devolve o custo total de um produto num dado mês em promoção ou em preço normal.
 * @param Faturacao fatura.
 * @param char* produto.
 * @param int mes.
 * @param char modo.
 * @return int.
 */
double get_total_precos_mes_produto(Faturacao fatura, char* produto, int mes, char modo);

/**
 * Devolve a quantidade total de um produto num dado mês em promoção ou em preço normal.
 * @param Faturacao fatura.
 * @param char* produto.
 * @param int mes.
 * @param char modo.
 * @return int.
 */
int get_total_quantidades_mes_produto(Faturacao fatura, char* produto, int mes, char modo);

/**
 * Devolve o total faturado num intervalo de meses.
 * @param Faturacao fatura.
 * @param int mes1.
 * @param int mes2.
 * @return double.
 */
double get_total_faturado_intervalo(Faturacao fatura, int mes1, int mes2);

/**
 * Devolve a quantidade total vendida num intervalo de meses.
 * @param Faturacao fatura.
 * @param int mes1.
 * @param int mes2.
 * @return int.
 */
int get_total_quantidades_intervalo(Faturacao fatura, int mes1, int mes2);

/**
 * ??????????????????????????????????????????????????????????????.
 * @param Conj_Faturas conjuto.
 * @param Conj_Faturas nao_comprados.
 * @param Faturacao faturas.
 * @param int filial.
 * @return Conj_Faturas.
 */
Conj_Faturas faturas_nao_comprado_filial(Conj_Faturas conjunto, Conj_Faturas nao_comprados,  Faturacao faturas, int filial);

/**
 * Inicializa uma lista de faturação.
 * @param int capacidade.
 * @return Conj_Faturas.
 */
Conj_Faturas init_Lista_Faturacao(int capacidade);

/**
 * Adiciona ao conjuto de faturas um produto.
 * @param Conj_Faturas conjuto.
 * @param char *info.
 * @return Conj_Faturas.
 */
Conj_Faturas adiciona_Conjunto(Conj_Faturas conjunto, char* info);

/**
 * Devolve o conjuto de produtos nunca comprados.
 * @param Conj_Faturas conjuto.
 * @param Faturacao faturacao.
 * @return Conj_Faturas.
 */
Conj_Faturas faturas_produtos_nao_comprados_totais(Conj_Faturas conjunto, Faturacao faturacao);

/**
 * Prepara o conjuto de faturas para ser apresentado.
 * @param Conj_Faturas conjuto.
 */
void apresenta_faturas(Conj_Faturas conjunto);

/**
 * Cria uma lista com todos os produtos da estrutura.
 * @param Conj_Faturas conjuto.
 * @param Faturacao faturacao.
 * @return Conj_Faturas.
 */
Conj_Faturas cria_lista_total(Conj_Faturas conjunto, Faturacao faturacao);

/**
 * Devolve um produto de uma lista.
 * @param Conj_Faturas conjuto.
 * @param int pos.
 * @return char*.
 */
char* get_elemento_lista(Conj_Faturas conjunto, int pos);

/**
 * Devolve a posiçao de um ????????????????????.
 * @param Conj_Faturas conjuto.
 * @return int.
 */
int faturacao_getPos(Conj_Faturas conjunto);

#endif