#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "valida.h"

#define MAXBUFFERSALES 128


/* Verifica as vendas, existência do cliente e do produto vendido. */

int validate_sales(CATALOG products, CATALOG costumers, struct sale *sales[1000000]) {
   
   char line[MAXBUFFERSALES];
   char* information;
   
   int i, verify, sales_yes = 0, index = 0, sales_no = 0, total = 0, indCli, indProd;

   char* product;
   double price;
   int ammount; 
   char type;
   char* client;
   int month;
   int shop;
   
   FILE *fp;

   fp = fopen("./data/Vendas_1M.txt","r");

   while(fgets(line,MAXBUFFERSALES,fp)) {

      information = strtok(line,"\n\r");
      information = strtok(information," ");
      
      for(i = 0; information != NULL; i++) {
         switch(i) {
            case 0: product = information;
            case 1: price = atof(information);
            case 2: ammount = atoi(information); 
            case 3: type = information[0];
            case 4: client = information;
            case 5: month = atoi(information);
            case 6: shop = atoi(information);
            default: break;
         }
         information = strtok(NULL," ");
      }

      /* Definição do indice a ocupar no array de AVL */
      
      indCli = client[0] -65;
      indProd = product[0] -65;
      
      /* Verifica a existencia do produto e do cliente de uma dada venda */

      verify = (verify_product(products->avl_list[indProd],product) && verify_client(costumers->avl_list[indCli],client));
      
      /* Caso verifique adiciona á estrutura das vendas a venda validada nessa monthma iteração */

      if(verify) {
         sales[index] = insert_sale(sales[index],product,price,ammount,type,client,month,shop);
         sales_yes++;
         total++;
         index++;
      } else {
         total++;
         sales_no++;
      }
   }
   
   fclose(fp);

   printf("Total de vendas analisadas: %d\n",total);
   printf("Total de vendas validas: %d\n",sales_yes);
   printf("Total de vendas falhadas: %d\n",sales_no);
   
   return sales_yes;
}

struct sale* insert_sale(struct sale *sales, char* product, double price, int ammount, char type, char* client, int month , int shop) {
   sales = malloc(sizeof(struct sale));
   sales->prod = malloc(strlen(product));
   strcpy(sales->prod,product);
   sales->price = price;
   sales->quantity = ammount;
   sales->type = type;
   sales->cli = malloc(strlen(client));
   strcpy(sales->cli,client);
   sales->month = month;
   sales->shop = shop;
   return sales;
}