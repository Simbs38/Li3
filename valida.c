#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "avl.h"
#include "valida.h"

#define MAXBUFFERVENDAS 128


/* Verifica as vendas, existência do cliente e do produto vendido. */

int valida_vendas(AVL produtos, AVL clientes,struct venda *vendas[1000000]) {
   
   char line[MAXBUFFERVENDAS];
   char* information;
   
   int i, verify, validos = 0, j = 0, falhados = 0, total = 0;

   char* product;
   double preco;
   int quantidade; 
   char tipo;
   char* client;
   int mes;
   int filial;
   
   FILE *fp;

   fp = fopen("./data/Vendas_1M.txt","r");

   while(fgets(line,MAXBUFFERVENDAS,fp)) {

      information = strtok(line,"\n\r");
      information = strtok(information," ");
      
      for(i = 0; information != NULL; i++) {
         switch(i) {
            case 0: product = information;
            case 1: preco = atof(information);
            case 2: quantidade = atoi(information); 
            case 3: tipo = information[0];
            case 4: client = information;
            case 5: mes = atoi(information);
            case 6: filial = atoi(information);
            default: break;
         }
         information = strtok(NULL," ");
      }
      
      verify = (verify_product(produtos,product) && verify_client(clientes,client));
      if(verify) {
         vendas[j] = malloc(sizeof(struct venda));
         vendas[j]->prod = malloc(strlen(product));
         strcpy(vendas[j]->prod,product);
         vendas[j]->price = preco;
         vendas[j]->quantity = quantidade;
         vendas[j]->type = tipo;
         vendas[j]->cli = malloc(strlen(client));
         strcpy(vendas[j]->cli,client);
         vendas[j]->month = mes;
         vendas[j]->shop = filial;
         validos++;
         j++;
         total++;
      }
      else {
         total++;
         falhados++;
      }
   }
   fclose(fp);

   printf("Total de vendas analisadas: %d\n",total);
   printf("Total de vendas validas: %d\n",validos);
   printf("Total de vendas falhadas: %d\n",falhados);
   
   return validos;
}