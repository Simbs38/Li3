#include "./headers/clientes.h"
#include "./headers/produtos.h"
#include "./headers/faturacao.h"
#include "./headers/interpretador.h"
#include "./headers/filiais.h"


int main() {
   int estado = 1;

   	while(estado) {	
    	
    	Cat_Clientes clientes = init_cat_clientes();
    	Cat_Produtos produtos = init_cat_produtos();
    	Faturacao faturacao = init_Faturacao();
        INFO_FILIAL info= init_filiais();

    	estado = menu_principal(produtos,clientes,faturacao,info, estado);


    	remove_Catalogo_Clientes(clientes);
    	remove_Catalogo_Produtos(produtos);
    	free_Faturacao(faturacao);
    
    }

    return 0;
}