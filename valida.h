#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "converte.h"

#define MAX_SIZE 50

void converte_produtos(char *produtos[]);

// Coloca o ficheiro dos clientes em memória. (terá de ser mudado para uma AVL por eficiencia)

void converte_clientes(char* clientes[]);

int valida_vendas(char* produtos[], char* clientes[]);

// Valida a existencia do cliente e produto numa venda.

int verifica(char* product, char* client, char* produtos[], char* clientes[]);
