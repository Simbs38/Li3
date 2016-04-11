#include "./headers/venda.h"

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


int getMes(Venda sale) {
    return sale->mes;
}


int getFilial(Venda sale) {
    return sale->filial;
}


int getQuantidade(Venda sale) {
    return sale->quantidade;
}


char getPromocao(Venda sale) {
    return sale->promocao;
}


double getPreco(Venda sale) {
    return sale->preco;
}



Boolean validate_sale(Cat_Produtos products, Cat_Clientes costumers, Venda venda) {
   return existe_Produto(products,getProduto(venda)) && existe_Cliente(costumers,getCliente(venda)) && 
            venda->mes >= 1 && venda->mes <= 12 && venda->quantidade > 0 && venda->quantidade <= 200 && venda->preco >= 0 && 
            venda->preco <= 999.99 && venda->filial > 0 && venda->filial < 4;
}