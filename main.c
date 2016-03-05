#include "main.h"
#include "check_prods.h"


int main() {

   char line[MAX_SIZE];
   char* informacao;
   char clientes[16385][6];
   char produtos[171009][7];
   
   int i = 0;
   
   FILE *fp;
   

   // COLOCA CLIENTES NUM ARRAY
   fp = fopen("Clientes.txt","r");
   while(fgets(line,MAX_SIZE,fp)) {
      informacao = strtok(line,"\n\r");
      strcpy(clientes[i],informacao);
      //printf("%s\n",clientes[i]);
      i++;
   }  
   fclose(fp);

   i = 0;
   fp = fopen("Produtos.txt","r");
   while(fgets(line,MAX_SIZE,fp)) {
      informacao = strtok(line,"\n\r");
      strcpy(produtos[i],informacao);
      //printf("%s\n",produtos[i]);
      i++;
   }  
   printf("%s\n",produtos[0]);

   return 0;
}

