#include "./headers/clientes.h"
#include "./headers/produtos.h"
#include "./headers/faturacao.h"
#include "./headers/interpretador.h"
#include "./headers/filial.h"

/**
 * Funcão main do programa que chamando auxiliares inicializa as estruturas, corre o programa e liberta o espaço alocado.
 * @return int.
 */
int main() {

    int estado = 1;
    int i;

   	while(estado) {
        	
    	Cat_Clientes clientes = init_cat_clientes();
    	Cat_Produtos produtos = init_cat_produtos();
    	Faturacao faturacao = init_Faturacao();
        Filial filiais[3];

        for(i = 0; i < 3; i++) {
            filiais[i] = init_Filial();
        }
        
    	estado = menu_principal(produtos,clientes,faturacao,filiais,estado);
        
        if(total_Produtos(produtos)) {
    	   remove_Catalogo_Clientes(clientes);
    	   remove_Catalogo_Produtos(produtos);
    	   free_Faturacao(faturacao);
            for(i = 0; i < 3; i++) free_Filial(filiais[i]);
        }
    }

    return 0;
}