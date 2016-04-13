#include "./headers/catalogo.h"

#define NR_LETRAS 26


struct catalogo {
   AVL indice[NR_LETRAS];
   int n;
};


struct array_catalogo {
  Lista list;
};


Catalogo init_Catalogo(int n) {


    Catalogo cat = (Catalogo) malloc(sizeof(struct catalogo));
    int i;
    cat->n=n;
    for(i = 0; i < n; i++) {
        cat->indice[i] = initAVL();
    }
    return cat;
}

Boolean existe_Catalogo(Catalogo catalogo, char* key,int index) {
   Boolean existe = avl_lookUp(catalogo->indice[index],key);

   return existe;
}


Catalogo insere_Catalogo(Catalogo catalogo, char* key, void* estrutura, int index) {
    catalogo->indice[index] = avl_insert(catalogo->indice[index], key, estrutura);
    
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


Catalogo clone_Catalogo(Catalogo catalogo) {
  int i;

  Catalogo novo = init_Catalogo(catalogo->n);

  for(i = 0; i < NR_LETRAS; i++) {
    novo->indice[i] = avl_clone(catalogo->indice[i]);
  }
  
  return novo;
}


void* getEstrutura_Catalogo(Catalogo catalogo, char* key, int index) {
  return avl_getEstrutura(catalogo->indice[index],key);
}



Array init_Array(int capacidade) {
    
    Array lista = (Array) malloc(sizeof(struct array_catalogo));
    lista->list = init_Lista(capacidade);
    
    return lista;
}


Array lista_catalogo_letra(Array lista,Catalogo catalogo, char letra) {
  
  int index = letra - 'A';
  lista->list = lista_converte(lista->list,catalogo->indice[index]);
  
  return lista;
}


Array adiciona_array(Array lista,char* info) {
  
  lista->list = lista_insert(lista->list,info);
  
  return lista;
}


Array catalogo_produtos_nao_comprados_totais(Array lista, Catalogo catalogo) {
  int i;
  
  for(i = 0; i < NR_LETRAS; i++) {
    lista->list = produtos_nao_comprados_totais(lista->list,catalogo->indice[i]);
  }
  
  return lista;
}


void apresenta_Array(Array lista) {
  apresenta_Lista(lista->list);
}


void imprimecat(Catalogo cat){

    int i,n=0;
    for(i=0;i!=26;i++){
      
      n+=imprimeavl(cat->indice[i],0);}
    
  }

Array catalogo_lista_total(Array lista,Catalogo catalogo) {
  int i;
  for(i = 0; i < 26; i++) {
    lista->list = lista_converte(lista->list,catalogo->indice[i]);
  }
  return lista;
}

char* catalogo_getElemento(Array lista, int pos) {
  return lista_getNome(lista->list,pos);
}

int catalogo_getPos(Array lista) {
  return lista_getPos(lista->list);
}