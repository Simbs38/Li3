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
    
    clock_t begin, end;
    double time_spent;

    begin = clock();
   
    int i, validated, conta = 0;
    
    CATALOG clients = init_catalog();
    CATALOG products = init_catalog();

    struct sale *sales[1000000];

    convert_clients(clients);
    convert_products(products);
    validated = validate_sales(products,clients,sales);

    for(i = 0; i<validated; i++) {
        if(sales[i]->price == 0) conta++;
    }
  
    printf("COMPRAS DE PRECO 0: %d\n", conta);

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("TEMPO DECORRIDO: %lf seconds\n",time_spent);
   
    return 0;
}