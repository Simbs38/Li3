#include "./headers/clientes.h"

#define NR_LETRAS 26
#define MAXBUFFERCLIENTES 32

struct cliente {
  char name[6];
};


struct catalogo_clientes {
  Catalogo catalogo;
};


Cat_Clientes init_cat_clientes() {
  Cat_Clientes catalog = malloc(sizeof(struct catalogo_clientes));
  catalog->catalogo = init_Catalogo(NR_LETRAS);
  return catalog;
}


Cliente criaCliente() {
  Cliente client = (struct cliente*) malloc(sizeof(struct cliente));
  return client;
}


void alteraCliente(Cliente client, char *info) {
    strncpy(client->name, info, 6);
}


void free_cliente(Cliente client) {
  free(client);
}

/* Função que verifica se um dado cliente existe no catalogo de clientes */


Boolean existe_Cliente(Cat_Clientes clients, Cliente client) {
  return existe_Catalogo(clients->catalogo,client->name,client->name[0]-'A');
}


Cat_Clientes insere_Cliente(Cat_Clientes clients, Cliente client) {
  clients->catalogo = insere_Catalogo(clients->catalogo,client->name,NULL,client->name[0]-'A');
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
  remove_Catalogo(clients->catalogo);
}

char* getNomeCliente(Cliente client) {
  return client->name;
}


Catalogo get_CatalogoCli(Cat_Clientes clientes) {
  return clientes->catalogo;
}