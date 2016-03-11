#include "valida.h"

<<<<<<< HEAD
=======
// Coloca o ficheiro dos produtos em memória. (terá de ser mudado para uma AVL por eficiencia)
   
void convert_products(char *produtos[]) {
   FILE *fp;
   char *information;
   char line[MAX_SIZE];
   int i = 0;
   
   fp = fopen("Produtos.txt","r");
   
   while(fgets(line,MAX_SIZE,fp)) {
      information = strtok(line,"\n\r");
      produtos[i] = malloc(6);
      strcpy(produtos[i],information);
      i++;
   }

   fclose(fp);
}


// Coloca o ficheiro dos clientes em memória. (terá de ser mudado para uma AVL por eficiencia)

void convert_clients(char* clientes[]) {
   
   FILE *fp;
   char *information;
   char line[MAX_SIZE];
   int i = 0;

   fp = fopen("Clientes.txt","r");

   while(fgets(line,MAX_SIZE,fp)) {
      information = strtok(line,"\n\r");
      clientes[i] = malloc(6);
      strcpy(clientes[i],information);
      i++;
   }

   fclose(fp);
}

>>>>>>> origin

// Verifica as vendas, existência do cliente e do produto vendido.

int valida_vendas(char* produtos[], char* clientes[]) {
   
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

int verify_existence(char* product, char* client, char* produtos[], char* clientes[]) {
   
   int i;
   int cl = 0, cp = 0; // variaveis de controlo da existencia do cliente e do produto
   
   for(i = 0; i < 171009; i++) {
      if(i < 16384 && !cl) {
         if(strcmp(client,clientes[i]) == 0) cl = 1;
      }  
      if(strcmp(product,produtos[i]) == 0) cp = 1;
      if(cl == 1 && cp == 1) break;
   }  
   return cl && cp;
}