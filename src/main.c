#include "./headers/clientes.h"
#include "./headers/produtos.h"
#include "./headers/faturacao.h"
#include "./headers/interpretador.h"

int main() {
   	
    Cat_Clientes clientes = init_cat_clientes();
    Cat_Produtos produtos = init_cat_produtos();
    Faturacao faturacao = init_Faturacao();

    menu_principal(produtos,clientes,faturacao);

    remove_Catalogo_Clientes(clientes);
    remove_Catalogo_Produtos(produtos);
    free_Faturacao(faturacao);
    
    return 0;
}