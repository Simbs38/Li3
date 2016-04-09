#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "./headers/clientes.h"
#include "./headers/produtos.h"
#include "./headers/leituras.h"
#include "./headers/faturacao.h"
#include "./headers/avl.h"

int main() {

   
    time_t begin = clock();

   
    Cat_Clientes costumers = init_cat_clientes();
    Cat_Produtos products = init_cat_produtos();
    Faturacao contas = init_Faturacao();
   	
    leitura_ficheiros(costumers,products,contas);
    
    time_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("TEMPO DECORRIDO: %lf seconds\n",time_spent);
    
    return 0;
}