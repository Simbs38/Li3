#include "clientes.h"

#define LETRAS 26

struct catalogo_clientes {
   AVL indice[LETRAS];
};


/* Coloca o ficheiro dos costumers em memória num array de AVL's */


Cat_Clientes init_cat_clientes(){

    Cat_Clientes catalog = malloc(sizeof(struct catalogo_clientes));

    int i;
    for(i = 0; i < LETRAS; i++) {
        catalog->indice[i] = initAVL();
    }
    
    return catalog;

}


int verify_exist_client(Cat_Clientes costumers, Cliente costumer) {
   
   int index = costumer[0] - 65; 
   int look_costumer = avl_lookUp(costumers->indice[index],costumer);
  
   return look_costumer;
}


Cat_Clientes insere_cliente(Cat_Clientes costumers, Cliente client) {
    
    int index = client[0] - 65;
    costumers->indice[index] = avl_insert(costumers->indice[index], client, NULL); 

    return costumers;
}