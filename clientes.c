#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>

#include "clientes.h"

#define MAXBUFFERCLIENTES 32

/* Coloca o ficheiro dos clientes em memória num array de AVL's */

void convert_clients(CATALOG clientes) {
   
   FILE *fp;
   char *information;
   char line[MAXBUFFERCLIENTES];
   int indice, contador = 0;

   fp = fopen("./data/Clientes.txt","r");

   while(fgets(line,MAXBUFFERCLIENTES,fp)) {
      information = strtok(line,"\n\r");
      indice = information[0] -65;
      clientes->letras[indice] = insert(clientes->letras[indice],information);
      contador++;
   }
   printf("Numero de clientes Validados: %d\n",contador);
   fclose(fp);
}


int verify_client(AVL clientes, char* client) {
   
   int look_client = lookUp(clientes,client);

   return look_client;
}