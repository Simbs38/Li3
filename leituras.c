#include "leituras.h"


static void convert_file_clients(Cat_Clientes costumers, FILE *f_clients);
static void convert_file_products(Cat_Produtos products, FILE *f_prods);


void leitura_ficheiros(Cat_Clientes costumers, Cat_Produtos products) {
	
   FILE *f_clients;
   FILE *f_prods;

   f_clients = fopen("./data/Clientes.txt","r");
   f_prods = fopen("./data/Produtos.txt","r");
   
   convert_file_clients(costumers,f_clients);
   convert_file_products(products,f_prods);
}


/* Coloca o ficheiro dos clientes em memória num array de AVL's */

static void convert_file_clients(Cat_Clientes costumers, FILE *f_clients) {
   
   char *information;
   char line[MAXBUFFERCLIENTES];
   int counter = 0;

   while(fgets(line,MAXBUFFERCLIENTES,f_clients)) {
      information = strtok(line,"\n\r");
      costumers = insere_cliente(costumers, information);
      counter++;
   }
   printf("Numero de clientes Validados: %d\n",counter);
   fclose(f_clients);
}


/* Coloca o ficheiro dos produtos em memória num array de AVL's */

static void convert_file_products(Cat_Produtos products, FILE *f_prods) {

   char *information;
   char line[MAXBUFFERPRODUTOS];
   int index, counter = 0;

   
   while(fgets(line,MAXBUFFERPRODUTOS,f_prods)) {
      information = strtok(line,"\n\r");
      products = insere_produto(products, information);
      counter++;
   }
   printf("Numero de produtos validos: %d\n",counter);
   fclose(f_prods);
}
