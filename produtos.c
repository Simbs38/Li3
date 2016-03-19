#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "produtos.h"

#define MAXBUFFERPRODUTOS 64


/* Coloca o ficheiro dos produtos em memória num array de AVL's */

void convert_products(CATALOG produtos) {
   FILE *fp;
   char *information;
   char line[MAXBUFFERPRODUTOS];
   int indice, contador = 0;

   fp = fopen("./data/Produtos.txt","r");
   
   while(fgets(line,MAXBUFFERPRODUTOS,fp)) {
      information = strtok(line,"\n\r");
      indice = information[0] -65;
      produtos->letras[indice] = insert(produtos->letras[indice],information);
      contador++;
   }
   printf("Numero de produtos validos: %d\n",contador);
   fclose(fp);
}

int verify_product(AVL produtos, char* product) {
   
   int look_product = lookUp(produtos,product);

   return look_product;
}