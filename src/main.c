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
        Filiais filiais = init_Filiais();

    	estado = menu_principal(produtos,clientes,faturacao,filiais,estado);

    	remove_Catalogo_Clientes(clientes);
    	remove_Catalogo_Produtos(produtos);
    	free_Faturacao(faturacao);
    }

    return 0;
}