#ifndef _clientes_h_
#define _clientes_h_

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "catalogo.h"
#include "global.h"

#define MAXBUFFERCLIENTES 32

typedef struct catalogo_clientes *Cat_Clientes;
typedef struct cliente *Cliente;

Cat_Clientes init_cat_clientes();
Cat_Clientes insere_Cliente(Cat_Clientes clients, Cliente client);
Cat_Clientes clone_Catalogo_Clientes(Cat_Clientes clients);
Boolean existe_Cliente(Cat_Clientes clients, Cliente costumer);
void remove_Catalogo_Clientes(Cat_Clientes clients);
int total_Clientes(Cat_Clientes clients);
int total_Clientes_letra(Cat_Clientes clients, char letra);

Cliente criaCliente();
void alteraCliente(Cliente client, char *info);
char* getNomeCliente(Cliente client);


#endif