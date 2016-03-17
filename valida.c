#include "valida.h"
#include "avl.h"
#include "main.h"

/*Coloca o ficheiro dos produtos em memória. (terá de ser mudado para uma AVL por eficiencia) */
   
struct node* convert_products(struct node *produtos) {
   FILE *fp;
   char *information;
   char line[MAXBUFFERPRODUTOS];
   
   fp = fopen("Produtos.txt","r");
   
   while(fgets(line,MAXBUFFERPRODUTOS,fp)) {
      information = strtok(line,"\n\r");
      produtos = insert(produtos,information);
   }

   fclose(fp);
   
   return produtos;
}


/* Coloca o ficheiro dos clientes em memória. (terá de ser mudado para uma AVL por eficiencia) */

struct node* convert_clients(struct node *clientes) {
   
   FILE *fp;
   char *information;
   char line[MAXBUFFERCLIENTES];
   
   fp = fopen("Clientes.txt","r");

   while(fgets(line,MAXBUFFERCLIENTES,fp)) {
      information = strtok(line,"\n\r");
      clientes = insert(clientes,information);
   }

   fclose(fp);
   return clientes;
}



/* Verifica as vendas, existência do cliente e do produto vendido. */

int valida_vendas(struct node *produtos, struct node *clientes,struct venda *vendas[1000000]) {
   
   char line[MAXBUFFERVENDAS];
   char* information;
   
   int i, verify, validos = 0, j = 0;

   char* product;
   double preco;
   int quantidade; 
   char tipo;
   char* client;
   int mes;
   int filial;
   
   FILE *fp;

   fp = fopen("Vendas_1M.txt","r");

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
      
      verify = verify_existence(product,client,produtos,clientes);
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
      }
   }
   fclose(fp);

   return validos;
}


/* Valida a existência do cliente e produto numa venda. */

int verify_existence(char* product, char* client, struct node *produtos, struct node *clientes) {
   
   int look_client = lookUp(clientes,client);
   int look_product = lookUp(produtos,product);

   return (look_client && look_product);
}