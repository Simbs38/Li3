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

Faturacao init_Faturacao();
Faturacao cria_Dados_Faturacao(Faturacao fact, Cat_Produtos);
Faturacao adiciona_Fatura(Faturacao contas, Venda venda);
void free_Faturacao(Faturacao faturacao);

Fatura_Produto init_Fatura_Produto();
void* getEstrutura_Faturacao(Faturacao faturacao, char* produto);


double get_total_precos_mes_produto_filial(Faturacao fatura, char* produto, int mes, char modo, int filial);
int get_total_quantidades_mes_produto_filial(Faturacao fatura, char* produto, int mes, char modo, int filial);
double get_total_precos_mes_produto(Faturacao fatura, char* produto, int mes, char modo);
int get_total_quantidades_mes_produto(Faturacao fatura, char* produto, int mes, char modo);
double get_total_faturado_intervalo(Faturacao fatura, int mes1, int mes2);
int get_total_quantidades_intervalo(Faturacao fatura, int mes1, int mes2);
Conj_Faturas faturas_nao_comprado_filial(Conj_Faturas conjunto, Conj_Faturas nao_comprados,  Faturacao faturas, int filial);

Conj_Faturas init_Lista_Faturacao(int capacidade);
Conj_Faturas adiciona_Conjunto(Conj_Faturas conjunto, char* info);
Conj_Faturas faturas_produtos_nao_comprados_totais(Conj_Faturas conjunto, Faturacao faturacao);
void apresenta_faturas(Conj_Faturas conjunto);
Conj_Faturas cria_lista_total(Conj_Faturas conjunto, Faturacao faturacao);
char* get_elemento_lista(Conj_Faturas conjunto, int pos);
int faturacao_getPos(Conj_Faturas conjunto);

#endif