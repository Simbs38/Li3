#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "avl.h"
#include "valida.h"
#include "clientes.h"
#include "produtos.h"


int main() {
    
    int i;
    
    CATALOG clients = (struct catalog*) malloc(sizeof(struct catalog));
    CATALOG products = (struct catalog*) malloc(sizeof(struct catalog));
    
    for(i = 0; i < 26; i++) {
        clients->letras[i] = NULL;
        products->letras[i] = NULL;
    }
    
    struct venda *vendas[1000000];

    int validated, conta = 0;

    convert_clients(clients);
    convert_products(products);
    validated = valida_vendas(products,clients,vendas);
    
   return 0;
}