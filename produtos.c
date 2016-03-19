#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"
#include "produtos.h"

#define MAXBUFFERPRODUTOS 64


/* Coloca o ficheiro dos produtos em memória */

AVL convert_products(AVL produtos) {
   FILE *fp;
   char *information;
   char line[MAXBUFFERPRODUTOS];
   
   fp = fopen("./data/Produtos.txt","r");
   
   while(fgets(line,MAXBUFFERPRODUTOS,fp)) {
      information = strtok(line,"\n\r");
      produtos = insert(produtos,information);
   }

   fclose(fp);
   
   return produtos;
}

int verify_product(AVL produtos, char* product) {
   
   int look_product = lookUp(produtos,product);

   return look_product;
}