#include "./headers/clientes.h"


#include <string.h> 
#include <stdlib.h>


struct cliente {
  char name[6];
};


struct catalogo_clientes {
  Catalogo catalogo;
};





/***********************
FUNCOES SOBRE UM CLIENTE
************************/

/**
 * Aloca e retorna um cliente.
 * @return Cliente.
 */
Cliente criaCliente() {
  Cliente client = (Cliente) malloc(sizeof(struct cliente));
  return client;
}

/**
 * Altera a informação de um cliente.
 * @param Cliente client.
 * @param char *info.
 */
void alteraCliente(Cliente client, char *info) {
    strcpy(client->name,info);
}

/**
 * Devolve o codigo de um cliente.
 * @param Cat_Clientes clients.
 * @return char *letra.
 */
char* getNomeCliente(Cliente client) {
  return client->name;
}

/**
 * Liberta o espaço alocado por um cliente.
 * @param Cliente client.
 */
void free_cliente(Cliente client) {
  free(client);
}


/*************************************
FUNCOES SOBRE UM CATALOGO DE CLIENTES
*************************************/
/**
 * Inicializa um catalogo de clientes.
 * @return Cat_Clientes.
 */
Cat_Clientes init_cat_clientes() {
  Cat_Clientes catalog = malloc(sizeof(struct catalogo_clientes));
  catalog->catalogo = init_Catalogo();
  return catalog;
}

/**
 * Função que verifica se um dado cliente existe no catalogo de clientes.
 * @param Cat_Clientes clients.
 * @param Cliente client.
 * @return Boolean com valor de verdade.
 */
Boolean existe_Cliente(Cat_Clientes clients, Cliente client) {
  return existe_Catalogo(clients->catalogo,client->name);
}

/**
 * Insere um cliente no catalogo de clientes.
 * @param Cat_Clientes clients.
 * @param Cliente client.
 * @return Cat_Clientes.
 */

Cat_Clientes insere_Cliente(Cat_Clientes clients, Cliente client) {
  clients->catalogo = insere_Catalogo(clients->catalogo,client->name,NULL);
  return clients;
}


/**
 * Cria um clone de um catalogo de clientes, retornando o endereço do novo catalogo.
 * @param Cat_Clientes clients.
 * @return Cat_Clientes.
 */
Cat_Clientes clone_Catalogo_Clientes(Cat_Clientes clients) {
  Cat_Clientes novo;
  novo->catalogo = clone_Catalogo(clients->catalogo);
  return novo;
}

/**
 * Devolve o numero de clientes num catalogo.
 * @param Cat_Clientes clients.
 * @return int.
 */
int total_Clientes(Cat_Clientes clients) {
  return total_elems_Catalogo(clients->catalogo);
}


/**
 * Devolve o numero de clientes começados com a letra indicada.
 * @param Cat_Clientes clients.
 * @param char letra.
 * @return int.
 */
int total_Clientes_letra(Cat_Clientes clients, char letra) {
  return total_elems_letra(clients->catalogo,letra);
}

/**
 * Liberta o espaço alocado em memoria pelo catalogo.
 * @param Cat_Clientes clients.
 */
void remove_Catalogo_Clientes(Cat_Clientes clients) {
  remove_Catalogo(clients->catalogo);
}

/**
 * Retorna o catalogo de clientes dentro da estrutura.
 * @param Cat_Clientes clients.
 * @return Catalogo.
 */
Catalogo get_CatalogoCli(Cat_Clientes clientes) {
  return clientes->catalogo;
}