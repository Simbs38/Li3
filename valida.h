#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 50

void convert_products(char *produtos[]);
void convert_clients(char* clientes[]);
int valida_vendas(char* produtos[], char* clientes[]);
int verify_existence(char* product, char* client, char* produtos[], char* clientes[]);