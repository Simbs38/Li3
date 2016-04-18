/**
 * @file faturacao.h
 * @brief Ficheiro que contem a API relativa ao modulo da Faturação Total.
 */

#ifndef _faturacao_h_
#define _faturacao_h_

#include <stdlib.h>

#include "produtos.h"
#include "venda.h"
#include "catalogo.h"
#include "global.h"

typedef struct faturacao *Faturacao;
typedef struct conjunto_faturas *Conj_Faturas;


/**
 * Inicia uma nova estrutura Faturação.
 * @return Nova estrutura Faturação.
 */
Faturacao init_Faturacao();


/**
 * Função responsavél por clonar o catalogo de produtos por forma a termos a informação previamente ordenada dos mesmos na faturação.
 * @param fact Faturação a inserir os dados.
 * @param produtos Cat_Produtos do qual provêm os dados.
 * @return Faturação com os dados já inseridos.
 */
Faturacao cria_Dados_Faturacao(Faturacao fat, Cat_Produtos produtos);


/**
 * Função adiciona_Fatura tem a responsabilidade da inserção dos dados provenientes de uma Venda na estrutura.
 * @param contas Faturacao onde será inserida a informação relativa á Venda.
 * @param venda Venda da qual provẽm os dados a inserir na Faturação.
 * @return contas Faturação após a inserção dos dados.
 */
Faturacao adiciona_Fatura(Faturacao contas, Venda venda);

/**
 * Função com o objetivo de limpar da memória uma estrutura Faturação.
 * @param faturacao Estrutura da Faturação a limpar da memória.
 */
void free_Faturacao(Faturacao faturacao);

/**
 * Devolve a faturação total de um produto num dado mês e numa dada filial em promoção ou em preço normal.
 * @param Faturacao fatura.
 * @param char* produto.
 * @param int mes.
 * @param char modo.
 * @param int filial.
 * @return double.
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
 * Devolve a quantidade total de produtos vendidos num intervalo de meses.
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

#endif /* _faturacao_h_ */