#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>

#include "clientes.h"

#define MAXBUFFERClientes 32

/* Coloca o ficheiro dos costumers em memória num array de AVL's */

void convert_clients(CATALOG costumers) {
   
   FILE *fp;
   char *information;
   char line[MAXBUFFERClientes];
   int index, counter = 0;

   fp = fopen("./data/costumers.txt","r");

   while(fgets(line,MAXBUFFERClientes,fp)) {
      information = strtok(line,"\n\r");
      index = information[0] -65;
      costumers->avl_list[index] = insert(costumers->avl_list[index],information);
      counter++;
   }
   printf("Numero de clientes Validados: %d\n",counter);
   fclose(fp);
}


int verify_client(AVL costumers, char* costumer) {
   
   int look_costumer = lookUp(costumers,costumer);

   return look_costumer;
}