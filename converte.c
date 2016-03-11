#include "converte.h"



// Coloca o ficheiro dos clientes em memória. (terá de ser mudado para uma AVL por eficiencia)




void converte_clientes(char* clientes[]) {
   
   FILE *fp;
   char *informacao;
   char line[MAX_SIZE];
   int i = 0;

   fp = fopen("Clientes.txt","r");

   while(fgets(line,MAX_SIZE,fp)) {
      informacao = strtok(line,"\n\r");
      clientes[i] = malloc(6);
      strcpy(clientes[i],informacao);
      i++;
   }

   fclose(fp);
}


// Coloca o ficheiro dos produtos em memória. (terá de ser mudado para uma AVL por eficiencia)
   


void converte_produtos(char *produtos[]) {
   FILE *fp;
   char *informacao;
   char line[MAX_SIZE];
   int i = 0;
   
   fp = fopen("Produtos.txt","r");
   
   while(fgets(line,MAX_SIZE,fp)) {
      informacao = strtok(line,"\n\r");
      produtos[i] = malloc(6);
      strcpy(produtos[i],informacao);
      i++;
   }

   fclose(fp);
}