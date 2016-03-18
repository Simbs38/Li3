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
    AVL clients = NULL;
    AVL products = NULL;
    /*CATALOG clients;
    CATALOG products;
    
    for(i = 0; i < 26; i++) {
        clients[i] = NULL;
        products[i] = NULL;
    }
    */
    struct venda *vendas[1000000];

    int validated, conta = 0;

    clients = convert_clients(clients);
    products = convert_products(products);
   
    validated = valida_vendas(products,clients,vendas);

   return 0;
}