#include "leituras.h"

static void convert_file_clients(Cat_Clientes costumers, FILE *f_clients);
static void convert_file_products(Cat_Produtos products, FILE *f_prods);
static void convert_file_sales(Cat_Produtos products, Cat_Clientes costumers, FILE *fp);
static Boolean validate_sale(Cat_Produtos products, Cat_Clientes costumers, Venda venda);

void leitura_ficheiros(Cat_Clientes costumers, Cat_Produtos products) {
	
   FILE *f_clients;
   FILE *f_prods;
   FILE *f_sales;

   f_clients = fopen("./data/Clientes.txt","r");
   f_prods = fopen("./data/Produtos.txt","r");
   f_sales = fopen("./data/Vendas_1M.txt","r");

   convert_file_clients(costumers,f_clients);
   convert_file_products(products,f_prods);
   convert_file_sales(products,costumers,f_sales);
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
   int counter = 0;

   
   while(fgets(line,MAXBUFFERPRODUTOS,f_prods)) {
      information = strtok(line,"\n\r");
      products = insere_produto(products, information);
      counter++;
   }
   printf("Numero de produtos validos: %d\n",counter);
   fclose(f_prods);
}


static void convert_file_sales(Cat_Produtos products, Cat_Clientes costumers, FILE *f_sales) {
   
   char line[MAXBUFFERVENDAS];
   char* information;
   
   int i, sales_yes = 0, sales_no = 0, total = 0;
   Boolean verify;

   char* product;
   double price;
   int ammount; 
   char type;
   char* client;
   int month;
   int shop;
   
   Venda venda = initVenda();

   while(fgets(line,MAXBUFFERVENDAS,f_sales)) {

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

      venda = record_sale(product,price,ammount,type,client,month,shop);
         
      /* Verifica a existencia do produto e do cliente de uma dada venda */
      
      verify = validate_sale(products,costumers,venda);
      
      /* Caso verifique adiciona á estrutura das vendas a venda validada nessa monthma iteração */

      if(verify) {
         sales_yes++;
         total++;
      } else {
         total++;
         sales_no++;
      }
   }
   
   fclose(f_sales);
   
   printf("Total de vendas analisadas: %d\n",total);
   printf("Total de vendas validas: %d\n",sales_yes);
   printf("Total de vendas falhadas: %d\n",sales_no);

}

static Boolean validate_sale(Cat_Produtos products, Cat_Clientes costumers, Venda venda) {
   return (existe_Produto(products,getProduto(venda)) && existe_Cliente(costumers,getCliente(venda)) );
}