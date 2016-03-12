#include "valida.h"
#include "avl.h"

// Coloca o ficheiro dos produtos em memória. (terá de ser mudado para uma AVL por eficiencia)
   
struct node* convert_products(struct node *produtos) {
   FILE *fp;
   char *information;
   char line[MAX_SIZE];
   
   fp = fopen("Produtos.txt","r");
   
   while(fgets(line,MAX_SIZE,fp)) {
      information = strtok(line,"\n\r");
      produtos = insert(produtos,information);
   }

   fclose(fp);
   
   return produtos;
}


// Coloca o ficheiro dos clientes em memória. (terá de ser mudado para uma AVL por eficiencia)

struct node* convert_clients(struct node *clientes) {
   
   FILE *fp;
   char *information;
   char line[MAX_SIZE];
   
   fp = fopen("Clientes.txt","r");

   while(fgets(line,MAX_SIZE,fp)) {
      information = strtok(line,"\n\r");
      clientes = insert(clientes,information);
   }

   fclose(fp);
   return clientes;
}


// Verifica as vendas, existência do cliente e do produto vendido.

int valida_vendas(struct node *produtos, struct node *clientes) {
   
   char line[MAX_SIZE];
   char* information;
   
   int i, verify, validos = 0;

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
      if(verify) validos++;
   }
   fclose(fp);

   return validos;
}


// Valida a existência do cliente e produto numa venda.

int verify_existence(char* product, char* client, struct node *produtos, struct node *clientes) {
   
   int look_client = lookUp(clientes,client);
   int look_product = lookUp(produtos,product);

   return (look_client && look_product);
}