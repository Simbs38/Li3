#include "./headers/leituras.h"


static Cat_Clientes converte_clientes(Cat_Clientes costumers, FILE *f_clients, char* file_name);
static Cat_Produtos converte_produtos(Cat_Produtos products, FILE *f_prods, char* file_name);
static void converte_vendas(Cat_Produtos products, Cat_Clientes costumers, Faturacao faturas, INFO_FILIAL info, FILE *fp,char* file_name);


void leitura_ficheiros(Cat_Clientes costumers, Cat_Produtos products, Faturacao contas,INFO_FILIAL info, FILE *f_clients, FILE *f_prods, FILE* f_sales, char* f_cname, char* f_pname, char* f_vname) {
   char continua[10];
   time_t begin, end;
   double time_spent;

   begin = clock();
   printf("\e[1;1H\e[2J");
   printf("\tLeitura dos ficheiros\n");
   costumers = converte_clientes(costumers,f_clients,f_cname);
   products = converte_produtos(products,f_prods,f_pname);   
   contas = cria_Dados_Faturacao(contas,products);
   info = full_init(info,products,costumers);
   converte_vendas(products,costumers,contas,info,f_sales,f_vname);
   printf("got 6\n");
   
   end = clock();
   time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   
   printf("Tempo total de leitura: %f segundos\n",time_spent);
   putchar('\n');
   printf("Prima uma tecla para continuar >> ");
   int input = scanf("%s",continua);
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
   printf("Tempo de Leitura: %f segundos\n",time_spent);
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
   printf("Tempo de Leitura: %f segundos\n",time_spent);
   putchar('\n');


   fclose(f_prods);
   return products;
}



static void converte_vendas(Cat_Produtos products, Cat_Clientes costumers, Faturacao faturas, INFO_FILIAL info ,FILE *f_sales,char* file_name) {
   
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
   printf("zxc\n");
   
   Venda venda = initVenda();
   printf("asdasda\n");
   while(fgets(line,MAXBUFFERVENDAS,f_sales)) {

      information = strtok(line,"\n\r");
      information = strtok(information," ");
      for(i = 0; information != NULL; i++) {
         switch(i) {
            case 0: product = information;break;
            case 1: price = atof(information); break;
            case 2: ammount = atoi(information);break; 
            case 3: type = information[0];break;
            case 4: client = information;break;
            case 5: month = atoi(information);break;
            case 6: shop = atoi(information);break;
            default: break;
         }
         information = strtok(NULL," ");
      }
      printf("got qwe\n");
      change_sale(venda,product,price,ammount,type,client,month,shop);
         
      /* Verifica a existencia do produto e do cliente de uma dada venda */
      
      verify = validate_sale(products,costumers,venda);
      /* Caso verifique adiciona á estrutura das vendas a venda validada nessa iteração */
      printf("got qwer\n");
      if(verify) {
         faturas = adiciona_Fatura(faturas,venda);

        info=insere_compra(info,venda);
         vendas_validas++;
         total++;
      } else {
         total++;
      }

   }
   printf("got asd\n");
   end = clock();
   time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

   nuncaComprados(info);

   
   printf("Nome do Ficheiro: %s\n",file_name);
   printf("Numero de linhas lidas: %d\n",total);
   printf("Numero de linhas válidas: %d\n",vendas_validas);
   printf("Numero de vendas inválidas: %d\n",total-vendas_validas);
   printf("Tempo de Leitura: %lf segundos\n",time_spent);
   putchar('\n');   

   fclose(f_sales);   
}

