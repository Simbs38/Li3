#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "clientes.h"
#include "produtos.h"
#include "leituras.h"
#include "catalogo.h"
#include "faturacao.h"
#include "avl.h"

int main() {

    
    clock_t begin = clock();
    
    Cat_Clientes costumers = init_cat_clientes();
    Cat_Produtos products = init_cat_produtos();
	Faturacao contas = init_Faturacao();

    leitura_ficheiros(costumers,products,contas);
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("TEMPO DECORRIDO: %lf seconds\n",time_spent);
    
    return 0;
}