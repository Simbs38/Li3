#ifndef _clientes_h_
#define _clientes_h_

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>

#include "avl.h"

#define MAXBUFFERClientes 32


typedef AVL Clientes;
typedef struct catalogo_clientes *Cat_Clientes;
typedef char* Cliente;

Cat_Clientes init_cat_clientes();
Cat_Clientes insere_cliente(Cat_Clientes costumers, Cliente client);
Boolean existe_Cliente(Cat_Clientes costumers, Cliente costumer);
int total_Clientes(Cat_Clientes clients);
void remove_Catalogo_Clientes(Cat_Clientes clients);
int total_Clientes_letra(Cat_Clientes clients, char letra);

#endif