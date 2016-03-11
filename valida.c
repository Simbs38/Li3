#include "valida.h"


// Verifica as vendas, existência do cliente e do produto vendido.

int valida_vendas(char* produtos[], char* clientes[]) {
   
   char line[MAX_SIZE];
   char* informacao;
   int i;
   
   int verify;
   int validos = 0;

   char* product;
   double preco;
   int quantidade; 
   char tipo;
   char* client;
   int mes;
   int filial;
   
   FILE *fp;


   fp = fopen("Vendas_1M.txt","r");

   while(fgets(line,MAX_SIZE,fp)) {

   informacao = strtok(line,"\n\r");
   
      informacao = strtok(informacao," ");
      for(i = 0; informacao != NULL; i++) {
         switch(i) {
            case 0: product = informacao;
            case 1: preco = atof(informacao);
            case 2: quantidade = atoi(informacao); 
            case 3: tipo = informacao[0];
            case 4: client = informacao;
            case 5: mes = atoi(informacao);
            case 6: filial = atoi(informacao);
            default: break;
         }
         informacao = strtok(NULL," ");
      }
      
      verify = verifica(product,client,produtos,clientes);
      if(verify) validos++;
   }
   fclose(fp);
   return validos;
}


// Valida a existencia do cliente e produto numa venda.

int verifica(char* product, char* client, char* produtos[], char* clientes[]) {
   
   int i, cl = 0, cp = 0;
   
   for(i = 0; i < 171009; i++) {
      if(i < 16384 && !cl) {
         if(strcmp(client,clientes[i]) == 0) cl = 1;
      }
      if(strcmp(product,produtos[i]) == 0) cp = 1;
      if(cl == 1 && cp == 1) break;
   }
   return cl && cp;
}
