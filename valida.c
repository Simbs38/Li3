#include "valida.h"

static struct sale* insert_sale(struct sale *sales, char* product, double price, int ammount, char type, char* client, int month , int shop);


/* Verifica as vendas, existência do cliente e do produto vendido. */

int validate_sales(Cat_Produtos products, Cat_Clientes costumers, struct sale *sales[1000000]) {
   
   char line[MAXBUFFERVENDAS];
   char* information;
   
   int i, verify, sales_yes = 0, index = 0, sales_no = 0, total = 0;

   char* product;
   double price;
   int ammount; 
   char type;
   char* client;
   int month;
   int shop;
   
   FILE *fp;

   fp = fopen("./data/Vendas_1M.txt","r");

   while(fgets(line,MAXBUFFERVENDAS,fp)) {

      information = strtok(line,"\n\r");
      information = strtok(information," ");
      for(i = 0; information != NULL; i++) {
         switch(i) {
            case 0: product = information;break;
            case 1: price = atof(information);break;
            case 2: ammount = atoi(information);break; 
            case 3: type = information[0];break;
            case 4: client = information;break;
            case 5: month = atoi(information);break;
            case 6: shop = atoi(information);break;
            default: break;
         }
         information = strtok(NULL," ");
      }
      
      /* Verifica a existencia do produto e do cliente de uma dada venda */
      
      verify = (verify_exist_product(products,product) && verify_exist_client(costumers,client));
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

static struct sale* insert_sale(struct sale *sales, char* product, double price, int ammount, char type, char* client, int month , int shop) {
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