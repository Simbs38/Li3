#include "main.h"
#include "valida.h"
#include "avl.h"

int main() {
   
	
    long clients;
    long products;
    struct venda *vendas[1000000];

    int validated, i, conta = 0;

    clients = convert_clients(clients);
    products = convert_products(products);
    
    validated = valida_vendas(products,clients,vendas);
    /*
    for(i = 0; i < validated; i++) {
    	if(strcmp(vendas[i]->cli,"Z5000") == 0) {
    		conta+=vendas[i]->quantity;
    	}
    }
    */
    printf("Validos: %d\n",validated);
    //printf("0 : %d\n", conta);
   return 0;
}
