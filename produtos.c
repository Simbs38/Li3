#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "produtos.h"

#define MAXBUFFERProducts  64


/* Coloca o ficheiro dos produtos em memória num array de AVL's */

void convert_products(CATALOG products) {
   FILE *fp;
   char *information;
   char line[MAXBUFFERProducts];
   int index, counter = 0;

   fp = fopen("./data/products.txt","r");
   
   while(fgets(line,MAXBUFFERProducts,fp)) {
      information = strtok(line,"\n\r");
      index = information[0] -65;
      products->avl_list[index] = insert(products->avl_list[index],information);
      counter++;
   }
   printf("Numero de produtos validos: %d\n",counter);
   fclose(fp);
}

int verify_product(AVL products, char* product) {
   
   int look_product = lookUp(products,product);

   return look_product;
}