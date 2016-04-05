#ifndef _clientes_h_
#define _clientes_h_

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>

#include "avl.h"
#include "catalogo.h"

#define MAXBUFFERCLIENTES 32

typedef struct catalogo_clientes *Cat_Clientes;
typedef struct cliente *Cliente;

Cliente criaCliente(char* info);
void alteraCliente(Cliente client, char *info);
Cat_Clientes init_cat_clientes();
Cat_Clientes insere_Cliente(Cat_Clientes clients, Cliente client);
Boolean existe_Cliente(Cat_Clientes clients, Cliente costumer);
int total_Clientes(Cat_Clientes clients);
void remove_Catalogo_Clientes(Cat_Clientes clients);
int total_Clientes_letra(Cat_Clientes clients, char letra);
char* getNomeCliente(Cliente client);

#endif