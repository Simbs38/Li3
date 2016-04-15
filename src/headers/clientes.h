#ifndef _clientes_h_
#define _clientes_h_

#include <string.h> 
#include <stdlib.h>

#include "catalogo.h"
#include "global.h"


typedef struct catalogo_clientes *Cat_Clientes;
typedef struct cliente *Cliente;



/**
 * Inicializa um catalogo de clientes.
 * @return Cat_Clientes.
 */
Cat_Clientes init_cat_clientes();

/**
 * Insere um cliente no catalogo de clientes.
 * @param Cat_Clientes clients.
 * @param Cliente client.
 * @return Cat_Clientes.
 */
Cat_Clientes insere_Cliente(Cat_Clientes clients, Cliente client);

/**
 * Cria um clone de um catalogo de clientes, retornando o endereço do novo catalogo.
 * @param Cat_Clientes clients.
 * @return Cat_Clientes.
 */
Cat_Clientes clone_Catalogo_Clientes(Cat_Clientes clients);

/**
 * Função que verifica se um dado cliente existe no catalogo de clientes.
 * @param Cat_Clientes clients.
 * @param Cliente client.
 * @return Boolean com valor de verdade.
 */
Boolean existe_Cliente(Cat_Clientes clients, Cliente costumer);

/**
 * Devolve o numero de clientes num catalogo.
 * @param Cat_Clientes clients.
 * @return int.
 */
int total_Clientes(Cat_Clientes clients);

/**
 * Devolve o numero de clientes começados com a letra indicada.
 * @param Cat_Clientes clients.
 * @param char letra.
 * @return int.
 */
int total_Clientes_letra(Cat_Clientes clients, char letra);

/**
 * Retorna o catalogo de clientes dentro da estrutura.
 * @param Cat_Clientes clients.
 * @return Catalogo.
 */
Catalogo get_CatalogoCli(Cat_Clientes clientes);

/**
 * Liberta o espaço alocado em memoria pelo catalogo.
 * @param Cat_Clientes clients.
 */
void remove_Catalogo_Clientes(Cat_Clientes clients);


/**
 * Aloca e retorna um cliente.
 * @return Cliente.
 */
Cliente criaCliente();

/**
 * Liberta o espaço alocado por um cliente.
 * @param Cliente client.
 */
void free_cliente(Cliente client);

/**
 * Altera a informação de um cliente.
 * @param Cliente client.
 * @param char *info.
 */
void alteraCliente(Cliente client, char *info);

/**
 * Devolve o codigo de um cliente.
 * @param Cat_Clientes clients.
 * @return char *letra.
 */
char* getNomeCliente(Cliente client);


#endif