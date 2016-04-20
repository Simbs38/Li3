#include "./headers/clientes.h"

#include <stdlib.h>
#include <string.h> 


struct cliente {
  char name[6];
};

struct catalogo_clientes {
  Catalogo catalogo;
};



Cliente criaCliente() {
  Cliente client = (Cliente) malloc(sizeof(struct cliente));
  return client;
}


void alteraCliente(Cliente client, char *info) {
    strcpy(client->name,info);
}


char* getNomeCliente(Cliente client, char* novo) {
  novo = malloc(6*sizeof(char));
  strncpy(novo,client->name,6);
  return novo;
}


void free_cliente(Cliente client) {
  free(client);
}


Cat_Clientes init_cat_clientes() {
  Cat_Clientes catalog = malloc(sizeof(struct catalogo_clientes));
  catalog->catalogo = init_Catalogo();
  return catalog;
}


Boolean existe_Cliente(Cat_Clientes clients, Cliente client) {
  return existe_Catalogo(clients->catalogo,client->name);
}


Cat_Clientes insere_Cliente(Cat_Clientes clients, Cliente client) {
  clients->catalogo = insere_Catalogo(clients->catalogo,client->name,NULL);
  return clients;
}


Cat_Clientes clone_Catalogo_Clientes(Cat_Clientes clients) {
  Cat_Clientes novo;
  novo->catalogo = clone_Catalogo(clients->catalogo);
  return novo;
}


int total_Clientes(Cat_Clientes clients) {
  return total_elems_Catalogo(clients->catalogo);
}


int total_Clientes_letra(Cat_Clientes clients, char letra) {
  return total_elems_letra(clients->catalogo,letra);
}


void remove_Catalogo_Clientes(Cat_Clientes clients) {
  remove_Catalogo(clients->catalogo,NULL);
}

Catalogo get_Catalogo_Clientes(Cat_Clientes clientes) {
  Catalogo novo = clone_Catalogo(clientes->catalogo);
  return novo;
}