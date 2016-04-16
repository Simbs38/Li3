#include "./headers/catalogo.h"

#define NR_LETRAS 26


struct catalogo {
   AVL indice[NR_LETRAS];
};


struct array_catalogo {
  Lista list;
};

/**
 * Inicializa um Catalogo returnando o mesmo.
 * @return Catalogo inicializado.
 */

Catalogo init_Catalogo() {

    Catalogo cat = (Catalogo) malloc(sizeof(struct catalogo));
    int i;
    for(i = 0; i < NR_LETRAS; i++) {
        cat->indice[i] = initAVL();
    }
    return cat;
}

/**
 * Verifica um valor existe no Catalogo returnando verdadeiro se existir e false caso contrario.
 * @param Catalogo catalogo.
 * @param key char* a procurar.
 * @param ind index, indice onde procurar no catalogo.
 * @return Boolean com valor verdadeiro ou falso.
 */

Boolean existe_Catalogo(Catalogo catalogo, char* key) {
   int index = key[0] - 'A';
   Boolean existe = avl_lookUp(catalogo->indice[index],key);

   return existe;
}


/**
 * Insere uma estrutura num nodo do Catalogo returnando o catalogo.
 * @param Catalogo catalogo.
 * @param key char* a procurar.
 * @param  void* estrutura estrutura a inserir no nodo.
 * @param ind index, indice onde procurar no catalogo.
 * @return Boolean com valor verdadeiro ou falso.
 */

Catalogo insere_Catalogo(Catalogo catalogo, char* key, void* estrutura) {
    int index = key[0] - 'A';
    catalogo->indice[index] = avl_insert(catalogo->indice[index], key, estrutura);
    
    return catalogo;
}

/**
 * Devolve o numero de nodos do catalogo.
 * @param Catalogo catalogo.
 * @return int.
 */

int total_elems_Catalogo(Catalogo catalogo) {
  
  int i, total = 0;
  
  for(i = 0; i < NR_LETRAS; i++) {
    total += avl_count(catalogo->indice[i]);
  }
  
  return total;
}


/**
 * Devolve o numero de nodos do catalogo começados pela letra dada.
 * @param char letra.
 * @param Catalogo catalogo.
 * @return int.
 */
int total_elems_letra(Catalogo catalogo, char letra) {
  
  int total = 0;
  int index = letra - 'A';
   
  total += avl_count(catalogo->indice[index]);

  return total;
}


/**
 * Liberta o espaço alocado na memoria para o catalogo.
 * @param Catalogo catalogo.
 */
void remove_Catalogo(Catalogo catalogo) {
  int i;
  
  for(i = 0; i < NR_LETRAS; i++) {
    avl_free(catalogo->indice[i]);
  }
}


/**
 * Cria um clone do catalogo dado, devolvendo uma copia deste.
 * @param Catalogo catalogo.
 * @return Catalogo catalogo.
 */
Catalogo clone_Catalogo(Catalogo catalogo) {
  int i;

  Catalogo novo = init_Catalogo();

  for(i = 0; i < NR_LETRAS; i++) {
    novo->indice[i] = avl_clone(catalogo->indice[i]);
  }
  
  return novo;
}


/**
 * Devolve o numero de nodos do catalogo.
 * @param Catalogo catalogo.
 * @return int.
 */
void* getEstrutura_Catalogo(Catalogo catalogo, char* key) {
  int index = key[0] - 'A';
  return avl_getEstrutura(catalogo->indice[index],key);
}



/**
 * Inicializa um array com a capacidade indicada.
 * @param int capacidade.
 * @return Array.
 */
Array init_Array(int capacidade) {
    
    Array lista = (Array) malloc(sizeof(struct array_catalogo));
    lista->list = init_Lista(capacidade);
    
    return lista;
}

/**
 * Converte uma parte de um catalogo para uma lista
 * @param Array lista que irá receber os dados.
 * @param Catalogo catalogo.
 * @param char letra, letra que indicara ao catalogo que elementos iram ser convertidos para a lista.
 * @return Array.
 */
Array lista_catalogo_letra(Array lista,Catalogo catalogo, char letra) {
  
  int index = letra - 'A';
  lista->list = lista_converte(lista->list,catalogo->indice[index]);
  
  return lista;
}

/**
 * Adiciona um elemento a uma Lista.
 * @param Array lista que irá receber os dados.
 * @param char *info palavra adicionada a Lista.
 * @return Array.
 */
Array adiciona_array(Array lista,char* info) {
  
  lista->list = lista_insert(lista->list,info);
  
  return lista;
}

/**
 * Retorna um array com todos os produtos não comprados.
 * @param Array lista onde serão alocados os dados.
 * @param Catalogo catalogo de onde se iram buscar os dados.
 * @return Array.
 */
Array catalogo_produtos_nao_comprados_totais(Array lista, Catalogo catalogo) {
  int i;
  
  for(i = 0; i < NR_LETRAS; i++) {
    lista->list = produtos_nao_comprados_totais(lista->list,catalogo->indice[i]);
  }
  
  return lista;
}

/**
 * Função responsavel de apresentar um Array.
 * @param Array lista de onde serão acedidos os dados.
 */
void apresenta_Array(Array lista) {
  apresenta_Lista(lista->list);
}

/**
 * Converte catalogo para lista??????????????????????????????????????????????????????????????????????????????????????????
 * @param Array lista.
 * @param Catalogo catalogo.
 * @return Array.
 */
Array catalogo_lista_total(Array lista,Catalogo catalogo) {
  int i;
  for(i = 0; i < 26; i++) {
    lista->list = lista_converte(lista->list,catalogo->indice[i]);
  }
  return lista;
}
/**
 * Devolve um elemento de uma lista na posição indicada
 * @param Array lista.
 * @param int pos, posição indicada pelo utilizador.
 * @return char *.
 */
char* catalogo_getElemento(Array lista, int pos) {
  return lista_getNome(lista->list,pos);
}
/**
 * Devolve o numero de posições atuais na alocadas na lista
 * @param Array lista.
 * @return int.
 */
int catalogo_getPos(Array lista) {
  return lista_getPos(lista->list);
}



Array catalogo_clientes_compraram_filial(Array lista, Catalogo catalogo) {
  int i;
  
  for(i = 0; i < NR_LETRAS; i++) {
    lista->list = clientes_compraram_filial(lista->list,catalogo->indice[i]);
  }
  
  return lista;
}
