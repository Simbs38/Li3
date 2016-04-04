#include "venda.h"

struct venda {
    char* produto;
    double preco;
    int quantidade; 
    char promocao;
    char* cliente;
    int mes;
    int filial;
};

Venda initVenda() {
	return NULL;
}

Venda record_sale(char* product, double price, int quantity, char promotion, char* client, int month, int shop) {

    struct venda* sale = (struct venda*) malloc(sizeof(struct venda));
    sale->produto = malloc(32);
    strcpy(sale->produto,product);
    sale->preco = price;
    sale->quantidade = quantity;
    sale->promocao = promotion;
    sale->cliente = malloc(32);
    strcpy(sale->cliente,client);
    sale->mes = month;
    sale->filial = shop;
    
    return sale;
}

void change_sale(Venda sale, char* product, double price, int quantity, char promotion, char* client, int month, int shop) {
    
    strcpy(sale->produto,product);
    sale->preco = price;
    sale->quantidade = quantity;
    sale->promocao = promotion;
    strcpy(sale->cliente,client);
    sale->mes = month;
    sale->filial = shop;
}

char* getProduto (Venda sale) {
    return sale->produto;
}

char* getCliente (Venda sale) {
    return sale->cliente;
}