#include "venda.h"

struct venda {
    Produto produto;
    double preco;
    int quantidade; 
    char promocao;
    Cliente cliente;
    int mes;
    int filial;
};

Venda initVenda() {
    Venda sale = (struct venda*) malloc(sizeof(struct venda));
    sale->produto = criaProduto("NA");
    sale->cliente = criaCliente("NA");
    return sale;
	
}

Venda record_sale(char* product, double price, int quantity, char promotion, char* client, int month, int shop) {

    Venda sale = (struct venda*) malloc(sizeof(struct venda));
    sale->produto = criaProduto(product);
    sale->preco = price;
    sale->quantidade = quantity;
    sale->promocao = promotion;
    sale->cliente = criaCliente(client);
    sale->mes = month;
    sale->filial = shop;
    
    return sale;
}

void change_sale(Venda sale, char* product, double price, int quantity, char promotion, char* client, int month, int shop) {
    
    alteraProduto(sale->produto,product);
    sale->preco = price;
    sale->quantidade = quantity;
    sale->promocao = promotion;
    alteraCliente(sale->cliente,client);
    sale->mes = month;
    sale->filial = shop;
}

Produto getProduto(Venda sale) {
    return sale->produto;
}

Cliente getCliente(Venda sale) {
    return sale->cliente;
}