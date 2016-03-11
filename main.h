#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "valida.h"
#include "converte.h"

#define MAX_SIZE 50


typedef struct clientes{
    char code[5];
    int balanceado;
    struct clientes *left, *right;
}Clientes;

typedef struct produtos{
    char code[6];
    int balanceado;
    struct produtos *left, *right;
}Produtos;


typedef struct vendas{
    char produto[6];
    float preco;
    int quantidade;
    char promocao;
    char cliente[5];
    char mes[2];
    char filial;
    int balanceado;
    struct vendas *left, *right;
}Vendas;
