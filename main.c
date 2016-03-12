#include "main.h"
#include "valida.h"
#include "avl.h"

int main() {
   
    struct node *clients = NULL;
    struct node *products = NULL;
    
    int validated;

    clients = convert_clients(clients);
    products = convert_products(products);
    
    validated = valida_vendas(products,clients);
    
    printf("Validos: %d\n",validated);
    
   return 0;
}