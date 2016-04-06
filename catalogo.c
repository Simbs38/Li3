#include "catalogo.h"

#define NR_LETRAS 26

struct catalogo {
   AVL indice[NR_LETRAS];
};

Catalogo init_Catalogo() {

    Catalogo cat = (struct catalogo*) malloc(sizeof(struct catalogo));
    int i;
    for(i = 0; i < NR_LETRAS; i++) {
        cat->indice[i] = initAVL();
    }
    return cat;
}

Boolean existe_Catalogo(Catalogo catalogo, char* key) {
   
   int index = key[0] - 'A';
   Boolean existe = avl_lookUp(catalogo->indice[index],key);

   return existe;
}

Catalogo insere_Catalogo(Catalogo catalogo, char* key) {
    int index = key[0] - 'A';
    catalogo->indice[index] = avl_insert(catalogo->indice[index], key, NULL);

    return catalogo;
}

int total_elems_Catalogo(Catalogo catalogo) {
  int i, total = 0;
  for(i = 0; i < NR_LETRAS; i++) {
    total += avl_count(catalogo->indice[i]);
  }
  return total;
}


int total_elems_letra(Catalogo catalogo, char letra) {
  
  int total = 0;
  int index = letra - 'A';
   
  total += avl_count(catalogo->indice[index]);

  return total;
}


void remove_Catalogo(Catalogo catalogo) {
  int i;
  for(i = 0; i < NR_LETRAS; i++) {
    avl_free(catalogo->indice[i]);
  }
}