#ifndef _interpretador_h_
#define _interpretador_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "produtos.h"
#include "clientes.h"
#include "faturacao.h"
#include "filiais.h"
#include "global.h"

/**
 * Função encarregue de imprimir o menu de interação principal com o utilizador e executar a sua primeira opção.
 * @param Cat_Protudos produtos.
 * @param Cat_Clientes clientes.
 * @param Faturacao faturas.
 * @param Filiais filiais.
 * @param int estado.
 * @return int.
 */
int menu_principal(Cat_Produtos produtos, Cat_Clientes clientes, Faturacao faturas,Filiais filiais,int estado);

/**
 * Função encarregue de imprimir o menu leitura de ficheiros.
 * @param Cat_Protudos produtos.
 * @param Cat_Clientes clientes.
 * @param Faturacao faturas.
 * @param Filiais filiais.
 * @return int.
 */
int menu_leitura(Cat_Produtos produtos, Cat_Clientes clientes,Faturacao faturas,Filiais filiais);

/**
 * Função encarregue de imprimir o menu do catalogo de produtos.
 * @param Cat_Protudos produtos.
 * @return int.
 */
int menu_catalogo(Cat_Produtos produtos);

/**
 * Função encarregue de imprimir o menu de faturação.
 * @param Faturacao faturas.
 * @return int.
 */
int menu_faturacao(Faturacao faturas);

/**
 * Função encarregue de imprimir o menu das filiais.
 * @param Filiais filiais.
 * @return int.
 */
int menu_filiais(Filiais filiais);


#endif
