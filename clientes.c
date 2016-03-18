#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>

#include "avl.h"
#include "clientes.h"

#define MAXBUFFERCLIENTES 32

/* Coloca o ficheiro dos clientes em memória numa AVL */

AVL convert_clients(AVL clientes) {
   
   FILE *fp;
   char *information;
   char line[MAXBUFFERCLIENTES];
   
   fp = fopen("./data/Clientes.txt","r");

   while(fgets(line,MAXBUFFERCLIENTES,fp)) {
      information = strtok(line,"\n\r");
      printf("%c\n",information[0]);
      clientes = insert(clientes,information);
   }

   fclose(fp);
   return clientes;
}


int verify_client(AVL clientes, char* client) {
   
   int look_client = lookUp(clientes,client);

   return look_client;
}