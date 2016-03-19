#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "valida.h"

#define MAXBUFFERVENDAS 128


/* Verifica as vendas, existência do cliente e do produto vendido. */

int valida_vendas(CATALOG produtos, CATALOG clientes, struct venda *vendas[1000000]) {
   
   char line[MAXBUFFERVENDAS];
   char* information;
   
   int i, verify, validos = 0, j = 0, falhados = 0, total = 0, indCLi, indProd;

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

      /* Definição do indice a ocupar no array de AVL */
      
      indCLi = client[0] -65;
      indProd = product[0] -65;
      
      /* Verifica a existencia do produto e do cliente de uma dada venda */

      verify = (verify_product(produtos->letras[indProd],product) && verify_client(clientes->letras[indCLi],client));
      
      /* Caso verifique adiciona á estrutura das vendas a venda validada nessa mesma iteração */

      if(verify) {
         vendas[j] = insert_sale(vendas[j],product,preco,quantidade,tipo,client,mes,filial);
         validos++;
         total++;
         j++;
      } else {
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

struct venda* insert_sale(struct venda *vendas, char* product, double preco, int quantidade, char tipo, char* client, int mes , int filial) {
   vendas = malloc(sizeof(struct venda));
   vendas->prod = malloc(strlen(product));
   strcpy(vendas->prod,product);
   vendas->price = preco;
   vendas->quantity = quantidade;
   vendas->type = tipo;
   vendas->cli = malloc(strlen(client));
   strcpy(vendas->cli,client);
   vendas->month = mes;
   vendas->shop = filial;
   return vendas;
}