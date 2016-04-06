#include "clientes.h"

#define NR_LETRAS 26

struct cliente {
  char* name;
};

struct catalogo_clientes {
  Catalogo catalogo;
};

Cat_Clientes init_cat_clientes() {
  Cat_Clientes catalog = malloc(sizeof(struct catalogo_clientes));
  catalog->catalogo = init_Catalogo();
  return catalog;
}

Cliente criaCliente(char* info) {
  struct cliente* client = (struct cliente*) malloc(sizeof(struct cliente));
  client->name = malloc(MAXBUFFERCLIENTES);
  strcpy(client->name,info);
  return client;
}


void alteraCliente(Cliente client, char *info) {
  strcpy(client->name,info);
}


/* Função que verifica se um dado cliente existe no catalogo de clientes */


Boolean existe_Cliente(Cat_Clientes clients, Cliente client) {
  return existe_Catalogo(clients->catalogo,getNomeCliente(client));
}


Cat_Clientes insere_Cliente(Cat_Clientes clients, Cliente client) {
  clients->catalogo = insere_Catalogo(clients->catalogo,getNomeCliente(client));
  return clients;

}


int total_Clientes(Cat_Clientes clients) {
  return total_elems_Catalogo(clients->catalogo);
}


int total_Clientes_letra(Cat_Clientes clients, char letra) {
  return total_elems_letra(clients->catalogo,letra);
}


void remove_Catalogo_Clientes(Cat_Clientes clients) {
  remove_Catalogo(clients->catalogo);
}

char* getNomeCliente(Cliente client) {
  return client->name;
}