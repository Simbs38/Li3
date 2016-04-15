#include "./headers/venda.h"

#include <string.h>
#include <stdlib.h>

struct venda {
    Produto produto;
    double preco;
    int quantidade; 
    char promocao;
    Cliente cliente;
    int mes;
    int filial;
};
/**
 * Inicializa a estrutura venda.
 * @return Venda.
 */
Venda initVenda() {
    Venda sale = (Venda) malloc(sizeof(struct venda));
    sale->produto = criaProduto();
    sale->cliente = criaCliente();
    return sale;
}


Venda change_sale(Venda sale, char* product, double price, int quantity, char promotion, char* client, int month, int shop) {    
    alteraProduto(sale->produto,product);
    sale->preco = price;
    sale->quantidade = quantity;
    sale->promocao = promotion;
    alteraCliente(sale->cliente,client);
    sale->mes = month;
    sale->filial = shop;

    return sale;
}

/**
 * Devolve o codigo do produto de uma venda.
 * @param Venda sale
 * @return Produto.
 */
Produto getProduto(Venda sale) {
    return sale->produto;
}

/**
 * Devolve o codigo do cliente de uma venda.
 * @param Venda sale
 * @return Produto.
 */
Cliente getCliente(Venda sale) {
    return sale->cliente;
}

/**
 * Devolve o mês do produto de uma venda.
 * @param Venda sale
 * @return int.
 */
int getMes(Venda sale) {
    return sale->mes;
}

/**
 * Devolve uma filiail.
 * @param Venda sale
 * @return int.
 */
int getFilial(Venda sale) {
    return sale->filial;
}

/**
 * Devolve a quantidade de um produto.
 * @param Venda sale
 * @return int.
 */
int getQuantidade(Venda sale) {
    return sale->quantidade;
}

/**
 * Devolve se a venda foi efetuada em P ou N.
 * @param Venda sale
 * @return char.
 */
char getPromocao(Venda sale) {
    return sale->promocao;
}

/**
 * Devolve o preço do produto de uma venda.
 * @param Venda sale
 * @return double.
 */
double getPreco(Venda sale) {
    return sale->preco;
}


/**
 * Valida a compra verificando todos os seus componentes.
 * @param Cat_Produtos products.
 * @param Cat_Clientes costumers.
 * @param Venda venda.
 * @return Boolean com valor de verdade.
 */
Boolean validate_sale(Cat_Produtos products, Cat_Clientes costumers, Venda venda) {
   return existe_Produto(products,getProduto(venda)) && existe_Cliente(costumers,getCliente(venda)) && 
            venda->mes >= 1 && venda->mes <= 12 && venda->quantidade > 0 && venda->quantidade <= 200 && venda->preco >= 0 && 
            venda->preco <= 999.99 && venda->filial > 0 && venda->filial < 4;
}