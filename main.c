#include "main.h"

int main() {

   char line[MAX_SIZE];
   char* informacao;

   // arrays de strings onde serão guardados em memória os dados dos ficheiros txt
   
   char clientes[16385][6];
   char produtos[171009][7];
   int i = 0;
   
   FILE *fp;

   // COLOCA CLIENTES NUM ARRAY (terá de ser mudado para uma arvore por eficiencia)
   
   fp = fopen("Clientes.txt","r");
   
   while(fgets(line,MAX_SIZE,fp)) {
      informacao = strtok(line,"\n\r");
      strcpy(clientes[i],informacao);
      i++;
   }  
   
   fclose(fp);

   // COLOCA PRODUTOS NUM ARRAY (terá de ser mudado para uma arvore por eficiencia)

   i = 0;
   fp = fopen("Produtos.txt","r");
   
   while(fgets(line,MAX_SIZE,fp)) {
      informacao = strtok(line,"\n\r");
      strcpy(produtos[i],informacao);
      i++;
   }
   
   fclose(fp);

   // VERIFICACAO DAS VENDAS (existência do cliente e do produto vendido -> arvore tambem)

   /*
   
   **CODE**

   */

   return 0;
}


