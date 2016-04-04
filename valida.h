#ifndef _valida_h_
#define _valida_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "produtos.h"
#include "clientes.h"

#define MAXBUFFERVENDAS 128

int validate_sales(Cat_Produtos products, Cat_Clientes costumers, struct sale *sales[1000000]);

#endif