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

int menu_principal(Cat_Produtos produtos, Cat_Clientes clientes, Faturacao faturas,Filiais filiais,int estado);
int menu_leitura(Cat_Produtos produtos, Cat_Clientes clientes,Faturacao faturas,Filiais filiais);
int menu_catalogo(Cat_Produtos produtos);
int menu_faturacao(Faturacao faturas);
int menu_filiais(Filiais filiais);


#endif
