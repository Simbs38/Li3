#include "produtos.h"

#define NR_LETRAS 26

struct catalogo_produtos {
   AVL indice[NR_LETRAS];
};

struct prod {
  AVL produto;
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

Boolean existe_Produto(Cat_Produtos products, Produto product) {
   
   int index = product[0] - 'A';
   Boolean existe = avl_lookUp(products->indice[index],product);

   return existe;
}


Cat_Produtos insere_produto(Cat_Produtos products, Produto prod) {
    int index = prod[0] - 'A';
    products->indice[index] = avl_insert(products->indice[index], prod, NULL);

    return products;
}


int total_Produtos(Cat_Produtos products) {
  int i, total = 0;
  for(i = 0; i < NR_LETRAS; i++) {
    total += avl_count(products->indice[i]);
  }
  return total;
}


int total_Produtos_letra(Cat_Produtos products, char letra) {
  
  int total = 0;
  int index = letra - 'A';
   
  total += avl_count(products->indice[index]);

  return total;
}



void remove_Catalogo_Produtos(Cat_Produtos products) {
  int i;
  for(i = 0; i < NR_LETRAS; i++) {
    avl_free(products->indice[i]);
  }
} 