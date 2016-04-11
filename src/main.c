#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "./headers/clientes.h"
#include "./headers/produtos.h"
#include "./headers/leituras.h"
#include "./headers/faturacao.h"
#include "./headers/filiais.h"
#include "./headers/avl.h"
#include "./headers/interpretador.h"


int main(int argc, char**argv) {
   	
    Cat_Clientes costumers = init_cat_clientes();
    Cat_Produtos products = init_cat_produtos();
    Faturacao contas = init_Faturacao();
    INFO_FILIAL info= init_filiais();

    leitura_ficheiros(argc, argv,costumers,products,contas,info);


    menu_principal(products,costumers,contas);

    return 0;
}