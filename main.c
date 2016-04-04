#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "avl.h"
#include "valida.h"
#include "clientes.h"
#include "produtos.h"
#include "leituras.h"

int main() {
    
    clock_t begin = clock();
    
    Cat_Clientes costumers = init_cat_clientes();
    Cat_Produtos products = init_cat_produtos();
    struct sale *sales[1000000];

    leitura_ficheiros(costumers,products);

    int validated = validate_sales(products,costumers,sales);
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("TEMPO DECORRIDO: %lf seconds\n",time_spent);
    
    return 0;
}