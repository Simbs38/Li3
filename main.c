#include "main.h"


int verifica(char* product, char* client, char* produtos[], char* clientes[]);

int main() {

   char line[MAX_SIZE];
   char* informacao;
   char* informacao2;

   // arrays de strings onde serão guardados em memória os dados dos ficheiros txt
   
   char* clientes[16385];
   char* produtos[171009];
   
   int contador = 0;
   int z;
   int i = 0;
   char* product;
   double preco;
   int quantidade; 
   char tipo;
   char* client;
   int mes;
   int filial;


   FILE *fp;

   // COLOCA CLIENTES NUM ARRAY (terá de ser mudado para uma AVL por eficiencia)
   
   fp = fopen("Clientes.txt","r");
   
   while(fgets(line,MAX_SIZE,fp)) {
      informacao = strtok(line,"\n\r");
      clientes[i] = malloc(6);
      strcpy(clientes[i],informacao);
      i++;
   }  
   
   fclose(fp);

   // COLOCA PRODUTOS NUM ARRAY (terá de ser mudado para uma AVL por eficiencia)
 
   i = 0;
   fp = fopen("Produtos.txt","r");
   
   while(fgets(line,MAX_SIZE,fp)) {
      informacao = strtok(line,"\n\r");
      produtos[i] = malloc(7);
      strcpy(produtos[i],informacao);
      i++;
   }
   
   fclose(fp);
  

   // VERIFICACAO DAS VENDAS (existência do cliente e do produto vendido -> arvore tambem)
   
   fp = fopen("Vendas_1M.txt","r");

   while(fgets(line,MAX_SIZE,fp)) {

   informacao = strtok(line,"\n\r");
   
      informacao = strtok(informacao," ");
      for(i = 0; informacao != NULL; i++) {
         switch(i) {
            case 0: product = informacao;
            case 1: preco = atof(informacao);
            case 2: quantidade = atoi(informacao); 
            case 3: tipo = informacao[0];
            case 4: client = informacao;
            case 5: mes = atoi(informacao);
            case 6: filial = atoi(informacao);
            default: break;
         }
         informacao = strtok(NULL," ");
      }
      z = verifica(product,client,produtos,clientes);
      if(z) contador++;
   }
   fclose(fp);
   printf("acertos: %d\n", contador);
   return 0;
}


int verifica(char* product, char* client, char* produtos[], char* clientes[]) {
   
   int i, cl = 0, cp = 0;
   
   for(i = 0; i < 171009; i++) {
      if(i < 16384 && !cl) {
         if(strcmp(client,clientes[i]) == 0) cl = 1;
      }
      if(strcmp(product,produtos[i]) == 0) cp = 1;
      if(cl == 1 && cp == 1) break;
   }
   return cl && cp;
}