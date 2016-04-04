#include "produtos.h"

#define NR_LETRAS 26

struct catalogo_produtos {
   AVL indice[NR_LETRAS];
};


Cat_Produtos init_cat_produtos() {

    Cat_Produtos cat = (struct catalogo_produtos*) malloc(sizeof(struct catalogo_produtos));
    int i;
    for(i = 0; i < NR_LETRAS; i++) {
        cat->indice[i] = initAVL();
    }
    return cat;
}


/* Função que verifica se um dado produto existe no catalogo de produtos */

int verify_exist_product(Cat_Produtos products, Produto product) {
   
   int index = product[0] - 'A';
   int existe = avl_lookUp(products->indice[index],product);

   return existe;
}


Cat_Produtos insere_produto(Cat_Produtos products, Produto prod) {
    int index = prod[0] - 'A';
    products->indice[index] = avl_insert(products->indice[index], prod, NULL);

    return products;
}