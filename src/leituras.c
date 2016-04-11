#include "./headers/leituras.h"


static Cat_Clientes converte_clientes(Cat_Clientes costumers, FILE *f_clients, char* file_name);
static Cat_Produtos converte_produtos(Cat_Produtos products, FILE *f_prods, char* file_name);
static void converte_vendas(Cat_Produtos products, Cat_Clientes costumers, Faturacao faturas, FILE *fp,char* file_name);


void leitura_ficheiros(int argc, char** argv, Cat_Clientes costumers, Cat_Produtos products, Faturacao contas) {

   time_t begin, end;
   double time_spent;

   begin = clock();

   FILE *f_clients;
   FILE *f_prods;
   FILE *f_sales;
   char* f_cname;
   char* f_pname;
   char* f_vname;

   switch(argc) {
      case 1: f_cname = "./data/Clientes.txt";
              f_pname = "./data/Produtos.txt";
              f_vname = "./data/Vendas_1M.txt";
              f_clients = fopen(f_cname,"r");
              f_prods = fopen(f_pname,"r");
              f_sales = fopen(f_vname,"r");
              break;
      case 4: f_cname = argv[1];
              f_pname = argv[2];
              f_vname = argv[3];
              f_clients = fopen(f_cname,"r");
              f_prods = fopen(f_pname,"r");
              f_sales = fopen(f_vname,"r");
              break;
      default: printf("Os ficheiros não foram especificados corretamente.\n");
               break;
   }

   if(f_clients == NULL) {
      printf("Erro ao abrir o ficheiro indicado!\n");
      f_clients = fopen("./data/Clientes.txt","r");  
   }
   if(f_prods == NULL) {
      printf("Erro ao abrir o ficheiro indicado!\n");
      f_prods = fopen("./data/Produtos.txt","r");
   }
   if(f_sales == NULL) {
      printf("Erro ao abrir o ficheiro indicado!\n");
      f_sales = fopen("./data/Vendas_1M.txt","r");
   }

   printf("\e[1;1H\e[2J");
   printf("\tLeitura dos ficheiros\n");
   costumers = converte_clientes(costumers,f_clients,f_cname);
   products = converte_produtos(products,f_prods,f_pname);   
   contas = cria_Dados_Faturacao(contas,products);
   converte_vendas(products,costumers,contas,f_sales,f_vname);
   
   end = clock();
   time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   
   printf("Tempo total de leitura: %lf segundos\n",time_spent);
   putchar('\n');
}


/* Coloca o ficheiro dos clientes em memória num array de AVL's */

static Cat_Clientes converte_clientes(Cat_Clientes costumers, FILE *f_clients, char* file_name) {
   
   time_t begin, end;
   double time_spent;

   begin = clock();

   char *information;
   char line[MAXBUFFERCLIENTES];
   
   int clientes_validos = 0, total = 0;


   Cliente client = criaCliente();
   
   while(fgets(line,MAXBUFFERCLIENTES,f_clients)) {
      
      information = strtok(line,"\n\r");
      
      if(information != NULL) {
         
         alteraCliente(client,information);   
         costumers = insere_Cliente(costumers, client);   
      
         clientes_validos++;
      }

      total++;
   }

   end = clock();
   time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   
   printf("Nome do Ficheiro: %s\n",file_name);
   printf("Numero de linhas lidas: %d\n",total);
   printf("Numero de linhas validas: %d\n",clientes_validos);
   printf("Tempo de Leitura: %lf segundos\n",time_spent);
   putchar('\n');


   fclose(f_clients);
   
   return costumers;
}



/* Coloca o ficheiro dos produtos em memória num array de AVL's */

static Cat_Produtos converte_produtos(Cat_Produtos products, FILE *f_prods, char* file_name) {

   time_t begin, end;
   double time_spent;

   begin = clock();

   char *information;
   char line[MAXBUFFERPRODUTOS];
   int produtos_validos = 0, total = 0;


   Produto prod = criaProduto();
   
   while(fgets(line,MAXBUFFERPRODUTOS,f_prods)) {
      
      information = strtok(line,"\n\r");
      
      if(information != NULL) {
         
         alteraProduto(prod,information);
         products = insere_produto(products, prod);
         
         produtos_validos++;
      }
      total++;
   }


   end = clock();
   time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

   printf("Nome do Ficheiro: %s\n",file_name);
   printf("Numero de linhas lidas: %d\n",total);
   printf("Numero de linhas validas: %d\n",produtos_validos);
   printf("Tempo de Leitura: %lf segundos\n",time_spent);
   putchar('\n');


   fclose(f_prods);
   return products;
}



static void converte_vendas(Cat_Produtos products, Cat_Clientes costumers, Faturacao faturas ,FILE *f_sales,char* file_name) {
   
   time_t begin, end;
   double time_spent;

   begin = clock();

   char line[MAXBUFFERVENDAS];
   char* information;
   
   int i, vendas_validas = 0, total = 0;
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

      change_sale(venda,product,price,ammount,type,client,month,shop);
         
      /* Verifica a existencia do produto e do cliente de uma dada venda */
      
      verify = validate_sale(products,costumers,venda);
      
      /* Caso verifique adiciona á estrutura das vendas a venda validada nessa iteração */

      if(verify) {
         faturas = adiciona_Fatura(faturas,venda);
         vendas_validas++;
         total++;
      } else {
         total++;
      }

   }

   end = clock();
   time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   
   printf("Nome do Ficheiro: %s\n",file_name);
   printf("Numero de linhas lidas: %d\n",total);
   printf("Numero de linhas válidas: %d\n",vendas_validas);
   printf("Numero de vendas inválidas: %d\n",total-vendas_validas);
   printf("Tempo de Leitura: %lf segundos\n",time_spent);
   putchar('\n');   

   fclose(f_sales);   
}

