#include "main.h"
#include "valida.h"

int main() {
   
   char* clients[16385]; // array de strings para colocar os clientes.
   char* products[171009]; // array de strings para colocar os produtos.
   int validated;

   convert_clients(clients);
   convert_products(products);

   validated = valida_vendas(products,clients);

   printf("Acertos: %d\n",validated);

   return 0;
}