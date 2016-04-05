#include "clientes.h"

#define NR_LETRAS 26

struct catalogo_clientes {
   AVL indice[NR_LETRAS];
};


/* Coloca o ficheiro dos costumers em memória num array de AVL's */

Cat_Clientes init_cat_clientes(){

    Cat_Clientes catalog = malloc(sizeof(struct catalogo_clientes));

    int i;
    for(i = 0; i < NR_LETRAS; i++) {
        catalog->indice[i] = initAVL();
    }
    
    return catalog;
}


Boolean existe_Cliente(Cat_Clientes costumers, Cliente costumer) {
   
   int index = costumer[0] - 65; 
   Boolean look_costumer = avl_lookUp(costumers->indice[index],costumer);
  
   return look_costumer;
}


Cat_Clientes insere_cliente(Cat_Clientes costumers, Cliente client) {
    
    int index = client[0] - 65;
    costumers->indice[index] = avl_insert(costumers->indice[index], client, NULL); 

    return costumers;
}

int total_Clientes(Cat_Clientes clients) {
  int i, total = 0;
  for(i = 0; i < NR_LETRAS; i++) {
    total += avl_count(clients->indice[i]);
  }
  return total;
}


int total_Clientes_letra(Cat_Clientes clients, char letra) {
  
  int total = 0;
  int index = letra - 'A';
   
  total += avl_count(clients->indice[index]);

  return total;
}



void remove_Catalogo_Clientes(Cat_Clientes clients) {
  int i;
  for(i = 0; i < NR_LETRAS; i++) {
    avl_free(clients->indice[i]);
  }
} 