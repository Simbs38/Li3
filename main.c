#include "main.h"

int main() {


   // arrays de strings onde serão guardados em memória os dados dos ficheiros txt
   
   char* clientes[16385];
   char* produtos[171009];
   int validos;

   converte_clientes(clientes);
   converte_produtos(produtos);

   validos = valida_vendas(produtos,clientes);

   printf("acertos: %d\n",validos);

   return 0;
}